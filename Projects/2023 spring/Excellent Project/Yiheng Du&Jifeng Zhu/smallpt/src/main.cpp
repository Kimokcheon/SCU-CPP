#include <iostream>
#include <cmath>
#include <chrono>
#include <climits>
#include <algorithm>
#include <fstream>
#include <random>
#include <thread>
#include <functional>
#include <numeric>
#include <windows.h>
#include <utility>
#include "../include/RayTrace.h"
using namespace std;

// mt19937 seed(chrono::steady_clock::now().time_since_epoch().count());
// unsigned int rng(){ return seed(); }
// double rnd( ) { return rng() * 1. / UINT_MAX; }     // [0,1] rand

int w, h;
int samps;
Vec* pixel;
Ray cam;
double tx=0, ty=0;
Vec cx;
Vec cy;

void init(){
    w = 1024 , h = 768 ;  ////resolution ratio定义需要渲染图像的宽度（1024），高度（768）
    samps = 2000 ;        //sampling times采样次数
    pixel = new Vec[w*h];  //pixel
    cam=Ray(Vec(50,55,290), Vec(0,-0.1,-1).norm());          //camera (position , direction)，cam.o即原点位置，cam.d即方向
    tx=0, ty=0;
    if( abs(cam.d.x) <= eps && abs(cam.d.y) <= eps) tx = 1, ty = 1;
    ////设定幕布的宽度为 1，高度为 1，从而使得幕布的宽高比与像素尺寸的宽高比相同
    else if( abs(cam.d.x) <= eps )  tx = 1, ty = 0;
    else if( abs(cam.d.y) <= eps )  ty = 1, tx = 0;
    else tx = 1, ty = -cam.d.x / cam.d.y;
    cx = Vec(tx, ty, 0).norm() * (0.5135*w/h);
    //设定幕布本身的高度为 0.5135（配合像素尺寸的宽高比），从而使得幕布的宽度为 0.5135*w/h
    cy = (cx%cam.d).norm() * 0.5135;
    //设置幕布，抵达相机的光线穿透幕布时会在与幕布的交点处留下颜色
    return ;
}

double clamp(double x){
    if( x < 0 ) return 0;
    if( x > 1 ) return 1;
    return x;
}
int toInt(double x){
    return int( pow(clamp(x), 1/2.2)*255 + 0.5);
    //将浮点颜色值转换为整数表示的颜色值，以便输出到图像文件中
}

template <typename Iterator, typename T> class Rendering{
public:
    void operator() (Iterator first, Iterator last, T &r){
        for (; first != last; ++first){
            // 计算结果
            r =  r + radiance(*first, 0) * (1./samps);
        }
    }
};
// 分发任务的函数
template <typename Iterator, typename T>
T ParallelRendering(Iterator first, Iterator last, T &r){
    //计算迭代器中包含的元素数量
    const unsigned int len = distance(first, last);
    //若迭代器中没有元素则直接返回
    if (!len){
        return r;
    }

    //获取机器支持的并发线程数
    const unsigned int num_thread = thread::hardware_concurrency();

    //最终实际上每个线程处理的元素个数
    const unsigned int block_size = len / num_thread;
    //保存每个线程累加的结果
    vector<T> results(num_thread);
    //启动比num_thread - 1个线程，因为main函数本身已开启一个线程
    vector<thread> threads(num_thread - 1);

    //开始并行计算
    Iterator block_begin = first;
    for (unsigned int i = 0; i < (num_thread - 1); ++i){
        Iterator block_end = block_begin;
        //将迭代器向前推进一个块,到达当前块的末尾位置
        std::advance(block_end, block_size);
        //传递参数,通常情况下thread的构造函数将复制所提供的参数,需要将模板参数转为引用
        threads[i] = thread(Rendering<Iterator, T>(), block_begin, block_end, std::ref(results[i]));
        block_begin = block_end;
    }
    //处理最后一个线程,由于block_size = len / num_thread得到的结果不一定为整数,该线程处理剩余的所有元素
    Rendering<Iterator, T>()(block_begin, last, results[num_thread - 1]);
    //对threads中所有线程调用join()
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));

    return accumulate(results.begin(), results.end(), r) ;
}


// 计时结构
LARGE_INTEGER t1, t2, tc;

void time_begin(){
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
}

float time_end(){
    QueryPerformanceCounter(&t2);
    return ((t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart) * 1000;
}

//标准并行
void work_thread(){

    time_begin();

    Vec r;
    for (int y=0; y<h; ++y ){
        fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samps*4,100.*y/(h-1));
        for (int x=0; x<w; ++x){                //单个像素
            vector <Ray> i_vec(0);
            int i = (h-y-1)*w+x;
            for (int sy=0; sy<2; sy++)       // 2x2 subpixel rows//i为当前像素在 c 中的索引。
                for (int sx=0; sx<2; sx++, r=Vec())        // 2x2 subpixel cols//r是当前像素的颜色值，sx 和 sy：子像素索引，为 0 或 1
                    for (int s=0; s<samps; ++s){
                        //tent
                        double r1=rnd(), dx=r1<1 ? sqrt(r1)-1: 1-sqrt(2-r1);
                        double r2=rnd(), dy=r2<1 ? sqrt(r2)-1: 1-sqrt(2-r2);
                        //dx 和 dy：滤波后的随机自变量
                        //r1 和 r2：滤波用自变量
                        Vec d = cx*( ( (sx+0.5 + dx)/2 + x)/w - 0.5) +\
                                cy*( ( (sy+0.5 + dy)/2 + y)/h - 0.5) +\
                                cam.d;                      //d：相机射向幕布上某个子像素的方向向量

                        i_vec.push_back( Ray(cam.o+d*140,d.norm()) );
                    }// Camera rays are pushed forward to start in interior
            r=ParallelRendering(i_vec.cbegin(), i_vec.cend(), r);
            pixel[i] = pixel[i] + Vec(clamp(r.x),clamp(r.y),clamp(r.z)) * 0.25;
        }
    }

    cout << endl << "time: " << time_end() << endl;
    return ;
}

//openMP并行运算
void work_omp(){
    time_begin();
    Vec r;
#pragma omp parallel for schedule(dynamic, 1) private(r)
    for (int i=0; i<w*h; ++i){
        int x = i%w;
        int y = h - i/w - 1;
        for (int sy=0; sy<2; sy++)
            for (int sx=0; sx<2; sx++){
                r=Vec();
                for (int s=0; s<samps; ++s){
                    //tent
                    double r1=rnd(), dx=r1<1 ? sqrt(r1)-1: 1-sqrt(2-r1);
                    double r2=rnd(), dy=r2<1 ? sqrt(r2)-1: 1-sqrt(2-r2);

                    Vec d = cx*( ( (sx+0.5 + dx)/2 + x)/w - 0.5) +\
                            cy*( ( (sy+0.5 + dy)/2 + y)/h - 0.5) +\
                            cam.d;

                    r = r + radiance(Ray(cam.o+d*140,d.norm()), 0) * (1./samps);
                }
                pixel[i] = pixel[i] + Vec(clamp(r.x),clamp(r.y),clamp(r.z)) * 0.25;
            }
    }
    cout << "time: " << time_end() << endl;
    return ;
}

int main(){

    init();

    work_omp();
    // work_thread();

    ofstream fout("image.ppm");
    fout<<"P3"<<'\n'<<w<<' '<<h<<'\n'<<255<<'\n';
    for (int i=0; i<w*h; i++)
        fout<<toInt(pixel[i].x)<<' '<<toInt(pixel[i].y)<<' '<<toInt(pixel[i].z)<<' ';

    system("pause");
    return 0;
}