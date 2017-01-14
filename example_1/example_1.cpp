/* Constructor & Desctructor:
*
* Author: Victor Mondejar
*/
#include <exception>
#include <iostream>


class my_exception: public std::exception
{
  virtual const char* what() const throw()
  {
    return "My exception: points must be same dimension";
  }
} myex;

class Point
{
	public:

		//empty constructor 
		Point()
		{
			std::cout << "Creating instance Point with empty constructor..." << std::endl;
			_dim = -1;
		}

		//parametrized constructor
		Point(int dim)
		{
			try
			{
				std::cout << "Creating instance Point with parametrized constructor..." << std::endl;
				_dim = dim;
				_elems = new float[dim];
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		

//// OVERLOAD OPERATORS

		//my exception
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



		//destructor
		~Point()
		{
			std::cout << "Destroying instance Point..." << std::endl;
			if(_dim != -1)
				delete _elems;
		}

		////////////////////////////////////////////////////////

		float getValue(int index)
		{
			return _elems[index];
		}

		void setValue(int index, float val)
		{
			_elems[index] = val;
		}

		// Function to show on screen the values of Point instance
		void print()
		{
			if(_dim > 0)
			{
				std::cout<< "Point [";
				for(int i = 0; i < _dim-1; i++)
					std::cout << _elems[i] << ", ";

				std::cout<< _elems[_dim-1] << "] "<< std::endl;
			}
		}


	private:
		int _dim;
		float *_elems;
};

int main()
{
	// Instance created with empty constructor and without setting values
	Point a;
	a.print();


	// Instances created with parametrized constructor 
	Point p(3);
	p.setValue(0, 10);
	p.setValue(1, 2);
	p.setValue(2, 4);
	p.print();

	Point q(3);
	q.setValue(0, 2);
	q.setValue(1, 5);
	q.setValue(2, 2);
	q.print();

	// Overloading operators 
	std::cout<< "PQ = P + Q " << std::endl;
	Point pq = p + q;
	pq.print();

	// My exception: trying to add two points of different dimension
	Point b(1);
	b.setValue(0, 4);
	b.print();
	std::cout<< "PB = P + B" << std::endl;
	Point pb = p + b;
	pb.print();


	// Default exception: creating a point of negative dimensionality
	Point c(-1);


	return 0;
}