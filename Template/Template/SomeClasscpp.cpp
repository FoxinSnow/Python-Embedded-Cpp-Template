#include <iostream>
#include <vector>
#include "Python.h"
#include "SomeClass.h"

SomeClass::SomeClass()
{


}

SomeClass::~SomeClass()
{
	if (Py_IsInitialized())
	{
		Py_Finalize();
	}
}

void SomeClass::callScript()
{
	try {
		if (!Py_IsInitialized())
		{
			Py_Initialize();
		}

		PyObject* pModule = NULL;
		PyObject* pFunc = NULL;
		PyObject* args = NULL;

		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.argv = ['python.py']");
		PyRun_SimpleString("sys.path.append('../Template')");

		pModule = PyImport_ImportModule("script");
		if (!pModule) {
			throw "The python script cannot be opened.";
		}

		pFunc = PyObject_GetAttrString(pModule, "run");
		if (!pFunc || !PyCallable_Check(pFunc)) {
			throw "The python function cannot be called.";
		}

		//PyObject * parameters = PyTuple_New(4);
		//PyObject * para0 = Py_BuildValue("i", para_int0);
		//PyTuple_SetItem(parameters, 0, para0);
		PyObject * para1 = PyList_New(0);
		std::vector<int>::iterator it;
		for (it = para_vector.begin(); it != para_vector.end(); it++)
		{
			PyList_Append(para1, PyLong_FromLong(*it));
		}
		////PyObject * para1 = Py_BuildValue("[i, i]", para_int1, para_int2);
		//PyTuple_SetItem(parameters, 1, para1);
		//PyObject * para2 = Py_BuildValue("f", para_float);
		//PyTuple_SetItem(parameters, 2, para2);
		//PyObject * para3 = Py_BuildValue("s", para_string);
		//PyTuple_SetItem(parameters, 3, para3);

		PyObject * parameters = Py_BuildValue("(iOfs)", para_int0, para1, para_float, para_string);

		PyObject * returnValue = PyObject_CallObject(pFunc, parameters);

		if (!returnValue)
		{
			throw("Python script return value does not exist.");
		}

		double returned = PyFloat_AsDouble(returnValue);
		std::cout << "Python script returned " << returned << std::endl;
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (const char * c)
	{
		std::cout << "Exception: " << c << std::endl;
	}
}