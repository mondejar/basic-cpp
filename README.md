# basic_cpp

In this code a set of examples show some basic aspects and interesting properties of c++.

Compile
-------
To compile the examples type the follow:

```
mkdir build
cd build
cmake ..
make
```

- [Example 1](#Example)
  - [Constructor & Destructor](#Constructor_&_Destructor)
  - [Overload operators](#Overload_operators)
  - [Exceptions](#Exceptions)

# Example 1

## Constructor & Destructor
---------------------------

The constructor will be called when instances are created. 
```cpp
Point p;
```

If no constructor is specified a default empty constructor will be created.
```cpp
Point() {}
```

The constructor can be overloaded taking different parameters.
```cpp
//Empty constructor
Point() {_dim = -1;}

//parametrized constructor
Point(int dim)
{
	_dim = dim;
	_elems = new float[dim];
}
```

The destructor will be called when the instance lifetime ends. 
If no destructor is specified a default destructor will also be automatically created.
The implicitly default destructor will call the destructor for each member inside the class. 

The desctructor is then ideally when we must clean dynamically allocated memory from our instances.
```cpp
~Point()
{
	if(_dim != -1)
		delete _elems;
}
```


## Overload operators
---------------------
C++ allows the re-definition of the operators adapted to our classes.

```cpp
Point operator+(const Point& q) 
{
	Point p(this->_dim);
    for(int i = 0; i < this->_dim; i++)
    	p._elems[i] = this->_elems[i] + q._elems[i];
    return p;
}
```


## Exceptions
-------------
Exceptions provide a way to react to exceptional circumstances in programs by transferring control to special functions called handlers.
For example, suppose that we created an instance with parametrized constructor with negative value for dimension. 
An error "std::bad_array_new_length" would occur at the initialization of dynamic variable _elems. To avoid that we could use
the try catch block: 

```cpp
//parametrized constructor
Point(int dim)
{
	try
	{
		_dim = dim;
		_elems = new float[dim];
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
```

We could also define our own exceptions. Let's suppose now that in our overload operator + we try to add two points of different dimensions.
We may try to acces at some inexisten position of the _elems array. 

```cpp

class my_exception: public std::exception
{
  virtual const char* what() const throw()
  {
    return "My exception: points must be same dimension";
  }
} myex;


Point operator+(const Point& q) 
{
	Point p(this->_dim);
			
    try
	{
		if(this->_dim != q._dim)
			throw myex;

		for(int i = 0; i < this->_dim; i++)
			p._elems[i] = this->_elems[i] + q._elems[i];					
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return p;
}
```

