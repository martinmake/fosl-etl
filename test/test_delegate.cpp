/******************************************************************************
The MIT License(MIT)

Embedded Template Library.
https://github.com/ETLCPP/etl
http://www.etlcpp.com

Copyright(c) 2014 jwellbelove

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#include "UnitTest++.h"

#include "etl/private/delegate.h"

namespace
{
  //*****************************************************************************
  const int VALUE1 = 1;
  const int VALUE2 = 2;
  bool function_called = false;
  bool parameter_correct = false;

  //*****************************************************************************
  // Test data structure.
  //*****************************************************************************
  struct Data
  {
    int d;
  };

  //*****************************************************************************
  // The free function taking no parameters.
  //*****************************************************************************
  void free_void()
  {
    function_called = true;
  }

  //*****************************************************************************
  // The free function taking an int parameter.
  //*****************************************************************************
  void free_int(int i, int j)
  {
    function_called = true;
    parameter_correct = (i == VALUE1) && (j == VALUE2);
  }

  //*****************************************************************************
  // The free function taking a Data reference parameter.
  //*****************************************************************************
  void free_reference(const Data& data, int j)
  {
    function_called = true;
    parameter_correct = (data.d == VALUE1) && (j = VALUE2);
  }

  //*****************************************************************************
  // The test class with member functions.
  //*****************************************************************************
  class Test
  {
  public:

    // void
    void member_void()
    {
      function_called = true;
    }

    void member_void_const() const
    {
      function_called = true;
    }

    // int
    void member_int(int i, int j)
    {
      function_called = true;
      parameter_correct = (i == VALUE1) && (j == VALUE2);
    }

    void member_int_const(int i, int j) const
    {
      function_called = true;
      parameter_correct = (i == VALUE1) && (j == VALUE2);
    }

    // reference
    void member_reference(const Data& data, int j)
    {
      function_called = true;
      parameter_correct = (data.d == VALUE1) && (j = VALUE2);
    }

    void member_reference_const(const Data& data, int j) const
    {
      function_called = true;
      parameter_correct = (data.d == VALUE1) && (j = VALUE2);
    }

    // static
    static void member_static(const Data& data, int j)
    {
      function_called = true;
      parameter_correct = (data.d == VALUE1) && (j = VALUE2);
    }
  };

  Test test_static;
}

//*****************************************************************************
// Initialises the test results.
//*****************************************************************************
struct SetupFixture
{
  SetupFixture()
  {
    function_called   = false;
    parameter_correct = false;
  }
};

namespace
{
  SUITE(test_delegate)
  {
    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_free_void)
    {
      etl::delegate<void(void)> d = etl::delegate<void(void)>::create<free_void>();

      d();

      CHECK(function_called);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_const_free_void)
    {
      const etl::delegate<void(void)> d = etl::delegate<void(void)>::create<free_void>();

      d();

      CHECK(function_called);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_free_int)
    {
      etl::delegate<void(int, int)> d = etl::delegate<void(int, int)>::create<free_int>();

      d(VALUE1, VALUE2);

      CHECK(function_called);
      CHECK(parameter_correct);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_const_free_int)
    {
      const etl::delegate<void(int, int)> d = etl::delegate<void(int, int)>::create<free_int>();

      d(VALUE1, VALUE2);

      CHECK(function_called);
      CHECK(parameter_correct);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_free_reference)
    {
      etl::delegate<void(const Data&, int)> d = etl::delegate<void(const Data&, int)>::create<free_reference>();

      Data data;
      data.d = VALUE1;

      d(data, VALUE2);

      CHECK(function_called);
      CHECK(parameter_correct);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_const_free_reference)
    {
      const etl::delegate<void(const Data&, int)> d = etl::delegate<void(const Data&, int)>::create<free_reference>();

      Data data;
      data.d = VALUE1;

      d(data, VALUE2);

      CHECK(function_called);
      CHECK(parameter_correct);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_member_void)
    {
      Test test;

      etl::delegate<void(void)> d = etl::delegate<void(void)>::create<Test, &Test::member_void>(&test);

      d();

      CHECK(function_called);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_member_void_const)
    {
      Test test;

      etl::delegate<void(void)> d = etl::delegate<void(void)>::create<Test, &Test::member_void_const>(&test);

      d();

      CHECK(function_called);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_const_member_void)
    {
      Test test;

      const etl::delegate<void(void)> d = etl::delegate<void(void)>::create<Test, &Test::member_void>(&test);

      d();

      CHECK(function_called);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_const_member_void_const)
    {
      Test test;

      const etl::delegate<void(void)> d = etl::delegate<void(void)>::create<Test, &Test::member_void_const>(&test);

      d();

      CHECK(function_called);
    }

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_member_int)
    //{
    //  Test test;
    //  etl::function<Test, int> function(test, &Test::member_int);

    //  call(function);

    //  CHECK(function_called);
    //  CHECK(parameter_correct);
    //}

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_member_int_const)
    //{
    //  Test test;
    //  etl::function<Test, int> function(test, &Test::member_int);

    //  call(function);

    //  CHECK(function_called);
    //  CHECK(parameter_correct);
    //}

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_const_member_int)
    //{
    //  Test test;
    //  const etl::function<Test, int> function(test, &Test::member_int);

    //  call(function);

    //  CHECK(function_called);
    //  CHECK(parameter_correct);
    //}

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_const_member_int_const)
    //{
    //  Test test;
    //  const etl::function<Test, int> function(test, &Test::member_int);

    //  call(function);

    //  CHECK(function_called);
    //  CHECK(parameter_correct);
    //}

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_member_reference)
    //{
    //  Test test;
    //  etl::function<Test, const Data&> function(test, &Test::member_reference);

    //  call(function);

    //  CHECK(function_called);
    //  CHECK(parameter_correct);
    //}

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_const_member_reference)
    //{
    //  Test test;
    //  const etl::function<Test, const Data&> function(test, &Test::member_reference);

    //  call(function);

    //  CHECK(function_called);
    //  CHECK(parameter_correct);
    //}

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_member_void_compile_time)
    //{
    //  Test test;
    //  etl::function_mv<Test, &Test::member_void> function(test);

    //  call(function);

    //  CHECK(function_called);
    //}

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_const_member_void_compile_time)
    //{
    //  Test test;
    //  const etl::function_mv<Test, &Test::member_void> function(test);

    //  call(function);

    //  CHECK(function_called);
    //}

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_member_int_compile_time)
    //{
    //  Test test;
    //  etl::function_mp<Test, int, &Test::member_int> function(test);

    //  call(function);

    //  CHECK(function_called);
    //  CHECK(parameter_correct);
    //}

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_const_member_int_compile_time)
    //{
    //  Test test;
    //  const etl::function_mp<Test, int, &Test::member_int> function(test);

    //  call(function);

    //  CHECK(function_called);
    //  CHECK(parameter_correct);
    //}

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_member_reference_compile_time)
    //{
    //  Test test;
    //  etl::function_mp<Test, const Data&, &Test::member_reference> function(test);

    //  call(function);

    //  CHECK(function_called);
    //  CHECK(parameter_correct);
    //}

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_const_member_reference_compile_time)
    //{
    //  Test test;
    //  const etl::function_mp<Test, const Data&, &Test::member_reference> function(test);

    //  call(function);

    //  CHECK(function_called);
    //  CHECK(parameter_correct);
    //}

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_instance_member_void_compile_time)
    {
      function_called = false;

      etl::delegate<void(void)> d = etl::delegate<void(void)>::create<Test, &test_static, &Test::member_void>();

      d();

      CHECK(function_called);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_const_instance_member_void_compile_time)
    {
      function_called = false;

      const etl::delegate<void(void)> d = etl::delegate<void(void)>::create<Test, &test_static, &Test::member_void>();

      d();

      CHECK(function_called);
    }

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_instance_member_parameter_compile_time)
    //{
    //  function_called = false;

    //  etl::function_imp<Test, int, test_static, &Test::member_int> function;

    //  call(function);

    //  CHECK(function_called);
    //}

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_const_instance_member_parameter_compile_time)
    //{
    //  function_called = false;

    //  const etl::function_imp<Test, int, test_static, &Test::member_int> function;

    //  call(function);

    //  CHECK(function_called);
    //}

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_instance_member_reference_compile_time)
    //{
    //  function_called = false;

    //  etl::function_imp<Test, const Data&, test_static, &Test::member_reference> function;

    //  call(function);

    //  CHECK(function_called);
    //}

    ////*************************************************************************
    //TEST_FIXTURE(SetupFixture, test_const_instance_member_reference_compile_time)
    //{
    //  function_called = false;

    //  const etl::function_imp<Test, const Data&, test_static, &Test::member_reference> function;

    //  call(function);

    //  CHECK(function_called);
    //}
  };
}