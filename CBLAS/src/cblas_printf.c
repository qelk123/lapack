/*
 * cblas_printf.c
 *
 * The program is a C interface to caxpy.
 *
 * Written by Keita Teranishi.  2/11/1998
 *
 */
#include "cblas.h"
#include "cblas_f77.h"
#include <stdio.h>
#include <Python.h>

void API_SUFFIX(cblas_printf)( const CBLAS_INT N, const void *alpha, const void *X,
                       const CBLAS_INT incX, void *Y, const CBLAS_INT incY)
{
  printf("this is cblas_printf!\n");
  // main.c  
  PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;  

  // 初始化 Python 解释器  
  Py_Initialize();  

  // 将当前目录添加到 Python 模块搜索路径  
  PyRun_SimpleString("import sys");  
  PyRun_SimpleString("sys.path.append(\"/home/liuyn/code/lapack/CBLAS/src\")");  

  // 导入 example 模块  
  pName = PyUnicode_FromString("example");  
  pModule = PyImport_Import(pName);  
  Py_DECREF(pName);  

  if (pModule != NULL) {  
      // 获取 hello 函数  
      pFunc = PyObject_GetAttrString(pModule, "hello");  

      if (pFunc && PyCallable_Check(pFunc)) {  
          // 创建参数，调用函数  
          pArgs = PyTuple_New(1);  
          pValue = PyUnicode_FromString("World");  
          PyTuple_SetItem(pArgs, 0, pValue);  

          pValue = PyObject_CallObject(pFunc, pArgs);  
          Py_DECREF(pArgs);  

          if (pValue != NULL) {  
              printf("Result: %s\n", PyUnicode_AsUTF8(pValue));  
              Py_DECREF(pValue);  
          } else {  
              PyErr_Print();  
          }  
      } else {  
          if (PyErr_Occurred()) {  
              PyErr_Print();  
          }  
          fprintf(stderr, "Cannot find function \"hello\"\n");  
      }  
      Py_XDECREF(pFunc);  
      Py_DECREF(pModule);  
  } else {  
      PyErr_Print();  
      fprintf(stderr, "Failed to load \"example\"\n");  
  }  

  // 关闭 Python 解释器  
  Py_FinalizeEx();  

  return;
}
