# Introduction to Caffe Model

## Profile

- CAFFE (Convolutional Architecture for Fast Feature Embedding) is a deep learning framework, originally developed at University of California, Berkeley. It is open source, under a BSD license. It is written in C++, with a Python interface.

## Main Frame

- **Blob**
- **Layer**
- **Net**
- **Solver**
- **Proto**

## Concrete Realization

### Layer 

- **Data layer**![image-20210605191510224](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605191510224.png)

- **Convolution layer**

  ![image-20210605191556619](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605191556619.png)

- **Pooling layer**

  ![image-20210605191654669](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605191654669.png)

- **Activation function**

  ![image-20210605191730899](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605191730899.png)

- **Inner_product**

  ![image-20210605192114046](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605192114046.png)

### Solver

- ![image-20210605192244965](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605192244965.png)

### Summary

- ![image-20210605192333358](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605192333358.png)

## Source Code Parsing

- ### Simple Factory

  **Factory :**  The core part, which is responsible for implementing the internal logic of creating all products. The Factory class can be called directly from the outside world to create the required objects.

  

  **Product:** The parent of all objects created by the factory class, encapsulating the public methods of the Product object. All concrete products are subclass objects

  

  **ConcreteProduct:** The creation target of the simple factory pattern. All objects created are instances of a concrete class. It implements abstract methods declared in abstract products.

  

  **Advantages:**

  1. Let users have less understanding of the product itself and reduce the difficulty of use.

  2. You only need to modify the implementation of the factory class's creation concrete object method.

  

- ### Source Code of Solver 

  ![image-20210605193140931](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605193140931.png)

  ![image-20210605193147357](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605193147357.png)

  Solver<Dtype>* CreateSolver(const SolverParameter& param)

  This function is the operation of createProduct in factory mode. The SolverRegistry factory class in Caffe can provide us with six products (optimization algorithm).

  The function of these six products is to achieve network parameter update, but the implementation way is not the same

  These products are similar to Operation in the Product class above. Each Solver inherits the Solve and Step functions. The only thing unique to each Solver is that the ApplyUpdate function executes a different function and the interface is consistent. It is also the same as the products produced by the factory as we said before, with the same functions and different details.

  **Solve function** 

  ![image-20210605193721630](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605193721630.png)

  **Step function**

  ![image-20210605193747801](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605193747801.png)

  **SolverRegistry factory class**

  ![image-20210605193831143](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605193831143.png)

  ![image-20210605193836770](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605193836770.png)

  The selection is not implemented directly using a branching structure. Instead, a map container is used, which takes "the type of a specific Solver as the Key and the Creator function pointer corresponding to a specific Solver as the Value. The selection can also be realized through this key-value mapping relationship.

  

  *Register the creator function in the map:*

  ![image-20210605193931413](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605193931413.png)

  First, call Registry() to get the container, make sure that there is no type keyword to be added in the container, and then add elements with Key of type and Value of Creator function.

  

  *Register the creator function in the map:*

  ![image-20210605194106159](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605194106159.png)

  

- ### Source Code of Net

  Net is the skeleton of the whole network. Net assembles the layers of the network together and coordinates the forward and backward calculations of each layer.

  

  *The key functions in the Net class:*

  1. ForwardBackward: Forward and Backward are called sequentially.

  2. ForwardFromTo(int start, int end) : Performs a forward pass from start layer to end layer, using a simple for loop.

  3. BackwardFromTo(int start, int end) : Similar to the forwardFromTo function above, it calls the backpass from the start layer to the end layer.

  

- ### Source Code of Layer

  Layer is the basic component unit of Net, such as a convolution Layer or a Pooling Layer.

  

  The two core methods of Layer are Forward and Backward.

  Forward: Performs a Forward calculation based on the BLOB vector passed in by bottom to save the result to top.

  Backward: Calculates the diff_ element of the corresponding blob in the bottom based on the incoming BLOB from the bottom and top.

  

  **Layer Base Class**

  ![image-20210605194438312](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605194438312.png)

  First get the Phase of the current network, be it train or test, initialize the *layerParameter*, *blobs_*  holds a vector that points to the *shared_ptr* pointer of the blob class. Then apply for space, and then copy the *blob* in the incoming *layer_param*. 

  ​                                                                                        ——Constructors

  ![image-20210605194714595](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605194714595.png)

  Here is the *SetUp* function, which is normally inherited without overriding it.

  ​                                                                                        ——Initialization

  ![image-20210605194832885](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605194832885.png)

  ![image-20210605194839487](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20210605194839487.png)

  Forward and Backward function interfaces. Inherited after the call calls its corresponding forward_cpu, backward_cpu or forward_gpu, backward_gpu.

  

  **Layer Subclass**

  There are many subclasses of the Layer class in Caffe. Like the common ones:

  Data_Layer, Conv_Layer, Pooling_Layer ...

  

  *Common Core:* 

  Implement its own special LayerSetup and Forward and Backward functions to implement the basic functionality of this layer in the network.

  

  *Advantages:* 

  This design pattern makes it easy for deep learning researchers to build their own neural network layer and integrate it into Caffe's overall environment.