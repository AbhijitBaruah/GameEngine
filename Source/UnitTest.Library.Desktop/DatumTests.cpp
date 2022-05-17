#include "pch.h"
#include "Datum.h"
#include "Foo.h"
#include "ToStringOverload.h"
#include "RTTI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine;
namespace UnitTestLibraryDesktop
{
	TEST_CLASS(DatumTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#if defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(Constructor)
		{
			Datum d;
			Assert::AreEqual(d.Type(), DatumTypes::Unknown);
			Assert::AreEqual(d.Size(), (size_t)0);
			Assert::AreEqual(d.Capacity(), (size_t)0);
		}
		TEST_METHOD(CopyConstructor)
		{
			Datum d1;
			d1.PushBack(10);
			d1.PushBack(10);
			Assert::AreEqual(d1.Size(), (size_t)2);
			Assert::AreEqual(d1.Capacity(), (size_t)10);
			Datum d2 = d1;
			Assert::AreEqual(d2.Size(), (size_t)2);
			Assert::AreEqual(d2.Capacity(), (size_t)10);
			Datum d3;
			d3.SetType(DatumTypes::String);
			Assert::AreEqual(d3.Size(), (size_t)0);
			Assert::AreEqual(d3.Capacity(), (size_t)0);
			std::string s1 = "";
			d3.PushBack(s1);
			Datum d4 = d3;
			Assert::AreEqual(d4.Size(), (size_t)1);
			Assert::AreEqual(d4.Capacity(), (size_t)10);
			int a[] = { 1,2 };
			Datum d8;
			d8.SetStorage(a, 2);
			d8.Set(10);
			Datum d7 = d8;
			Assert::AreEqual(d7.Size(), (size_t)2);
			Assert::AreEqual(d7.Capacity(), (size_t)2);
			Datum d9;
			d9.SetType(DatumTypes::Float);
			Assert::ExpectException<std::runtime_error>([&d9, &a] {d9.SetStorage(a, 10); });
		}
		TEST_METHOD(CopyConstructorOverloads)
		{
			{
				Datum d1 = 5;
				Assert::AreEqual(d1.Size(), (size_t)1);
				Assert::AreEqual(d1.Capacity(), (size_t)1);
				Assert::AreEqual(d1.Type(), DatumTypes::Integer);
				Assert::AreEqual(d1.Front<std::int32_t>(), 5);
			}
			{
				Datum d1 = 5.f;
				Assert::AreEqual(d1.Size(), (size_t)1);
				Assert::AreEqual(d1.Capacity(), (size_t)1);
				Assert::AreEqual(d1.Type(), DatumTypes::Float);
				Assert::AreEqual(d1.Front<float>(), 5.f);
			}
			{
				glm::vec4 v(1.f);
				Datum d1 = v;
				Assert::AreEqual(d1.Size(), (size_t)1);
				Assert::AreEqual(d1.Capacity(), (size_t)1);
				Assert::AreEqual(d1.Type(), DatumTypes::Vector);
				Assert::AreEqual(d1.Front<glm::vec4>(), v);
			}
			{
				glm::mat4 v(1.f);
				Datum d1 = v;
				Assert::AreEqual(d1.Size(), (size_t)1);
				Assert::AreEqual(d1.Capacity(), (size_t)1);
				Assert::AreEqual(d1.Type(), DatumTypes::Matrix);
				Assert::AreEqual(d1.Front<glm::mat4>(), v);
			}
			{
				std::string a = "abc";
				Datum d1 = a;
				Assert::AreEqual(d1.Size(), (size_t)1);
				Assert::AreEqual(d1.Capacity(), (size_t)1);
				Assert::AreEqual(d1.Type(), DatumTypes::String);
				Assert::AreEqual(d1.Front<std::string>(), a);
			}
			{
				Foo f1(10);
				RTTI* r = &f1;
				Datum d1 = r;
				Assert::AreEqual(d1.Size(), (size_t)1);
				Assert::AreEqual(d1.Capacity(), (size_t)1);
				Assert::AreEqual(d1.Type(), DatumTypes::Pointer);
				Assert::AreEqual(d1.Front<RTTI*>(), r);
			}
			
			
		}
		TEST_METHOD(AssignmentOperator)
		{
			{
				Datum d1;
				d1.PushBack(10);
				d1.PushBack(10);
				Assert::AreEqual(d1.Size(), (size_t)2);
				Assert::AreEqual(d1.Capacity(), (size_t)10);
				Datum d2;
				d2 = d1;
				Assert::AreEqual(d2.Size(), (size_t)2);
				Assert::AreEqual(d2.Capacity(), (size_t)10);
				Datum d3;
				d3.SetType(DatumTypes::String);
				Assert::AreEqual(d3.Size(), (size_t)0);
				Assert::AreEqual(d3.Capacity(), (size_t)0);
				std::string s1 = "";
				d3.PushBack(s1);
				Datum d4;
				d4 = d3;
				Assert::AreEqual(d4.Size(), (size_t)1);
				Assert::AreEqual(d4.Capacity(), (size_t)10);
				float a[] = { 1,2 };
				Datum d8;
				d8.SetStorage(a, 2);
				d8.Set(10.f);
				Datum d7;
				d7 = d8;
				Assert::AreEqual(d7.Size(), (size_t)2);
				Assert::AreEqual(d7.Capacity(), (size_t)2);
				Datum d9;
				d9.SetType(DatumTypes::Integer);
				Assert::ExpectException<std::runtime_error>([&d9, &a] {d9.SetStorage(a, 10); });
			}

			{
				Datum d1;
				d1 = 5;
				Assert::AreEqual(d1.Size(), (size_t)1);
				Assert::AreEqual(d1.Capacity(), (size_t)1);
				Assert::AreEqual(d1.Type(), DatumTypes::Integer);
				Datum d2;
				int a[] = { 10,20,30 };
				d2.SetStorage(a, 3);
				Assert::ExpectException<std::runtime_error>([&d2] {d2 = 5; });

			}

			{
				Datum d1;
				d1 = 5.f;
				Assert::AreEqual(d1.Size(), (size_t)1);
				Assert::AreEqual(d1.Capacity(), (size_t)1);
				Assert::AreEqual(d1.Type(), DatumTypes::Float);
				Datum d2;
				float a[] = { 10,20,30 };
				d2.SetStorage(a, 3);
				Assert::ExpectException<std::runtime_error>([&d2] {d2 = 5.f; });

			}

			{
				Datum d1;
				d1 = "Abc";
				Assert::AreEqual(d1.Size(), (size_t)1);
				Assert::AreEqual(d1.Capacity(), (size_t)1);
				Assert::AreEqual(d1.Type(), DatumTypes::String);
				Datum d2;
				std::string a[] = { "","","" };
				d2.SetStorage(a, 3);
				Assert::ExpectException<std::runtime_error>([&d2] {d2 = "asd"; });

			}

			{
				Datum d1;
				d1 = glm::vec4();
				Assert::AreEqual(d1.Size(), (size_t)1);
				Assert::AreEqual(d1.Capacity(), (size_t)1);
				Assert::AreEqual(d1.Type(), DatumTypes::Vector);
				Datum d2;
				glm::vec4 a[] = { {1.f,2.f,3.f,4.f }, {1.f, 2.f, 3.f, 4.f} };
				d2.SetStorage(a, 2);
				Assert::ExpectException<std::runtime_error>([&d2] {d2 = glm::vec4(); });

			}

			{
				Datum d1;
				d1 = glm::mat4();
				Assert::AreEqual(d1.Size(), (size_t)1);
				Assert::AreEqual(d1.Capacity(), (size_t)1);
				Assert::AreEqual(d1.Type(), DatumTypes::Matrix);
				Datum d2;
				glm::mat4 a[1];
				d2.SetStorage(a, 1);
				Assert::ExpectException<std::runtime_error>([&d2] {d2 = glm::mat4(); });

			}
			{
				Datum d1;
				Assert::AreEqual(d1.Size(), (size_t)0);
				Assert::AreEqual(d1.Capacity(), (size_t)0);
				Foo f1(10);
				RTTI* r = &f1;
				d1 = r;
				Assert::AreEqual(d1.Size(), (size_t)1);
				Assert::AreEqual(d1.Capacity(), (size_t)1);
				Assert::AreEqual(d1.Type(), DatumTypes::Pointer);
				Datum d2;
				RTTI* a = &f1;
				d2.SetStorage(&a, 10);
				Assert::ExpectException<std::runtime_error>([&d2] {  Foo F1(10); RTTI* r = &F1; d2 = r; });

			}
		}
		TEST_METHOD(Front)
		{

			{
				Datum d1;
				d1.PushBack(10);
				Assert::ExpectException<std::runtime_error>([&d1] {d1.Front<float>(); });
				const Datum d2 = d1;
				Assert::AreEqual(d2.Front<std::int32_t>(), 10);
				Assert::ExpectException<std::runtime_error>([&d2] {d2.Front<float>(); });
			}

			{
				Datum d1;
				d1.PushBack(10.f);
				Assert::ExpectException<std::runtime_error>([&d1] {d1.Front<std::int32_t>(); });
				const Datum d2 = d1;
				Assert::AreEqual(d2.Front<float>(), 10.f);
				Assert::ExpectException<std::runtime_error>([&d2] {d2.Front<std::int32_t>(); });
			}

			{
				Datum d1;
				glm::vec4 v1(1.f);
				d1.PushBack(v1);
				Assert::ExpectException<std::runtime_error>([&d1] {d1.Front<glm::mat4>(); });
				const Datum d2 = d1;
				Assert::AreEqual(d2.Front<glm::vec4>(), v1);
				Assert::ExpectException<std::runtime_error>([&d2] {d2.Front<glm::mat4>(); });
			}

			{
				Datum d1;
				glm::mat4 m1(1.f);
				d1.PushBack(m1);
				Assert::ExpectException<std::runtime_error>([&d1] {d1.Front<glm::vec4>(); });
				const Datum d2 = d1;
				Assert::AreEqual(d2.Front<glm::mat4>(), m1);
				Assert::ExpectException<std::runtime_error>([&d2] {d2.Front<glm::vec4>(); });
			}

			{
				Datum d1;
				Foo f1(10);
				RTTI* r;
				r = &f1;
				d1.PushBack(r);
				Assert::ExpectException<std::runtime_error>([&d1] {d1.Front<std::string>(); });
				const Datum d2 = d1;
				Assert::ExpectException<std::runtime_error>([&d2] {d2.Front<std::string>(); });
			}
			{
				Datum d1;
				std::string a = "abc";
				d1.PushBack(a);
				const Datum d2 = d1;
				Assert::AreEqual(d2.Front<std::string>(), a);
				Assert::ExpectException<std::runtime_error>([&d1] {d1.Front<RTTI*>(); });
				Assert::ExpectException<std::runtime_error>([&d2] {d2.Front<RTTI*>(); });
				
			}
		}

		TEST_METHOD(MoveSemantics)
		{
			Datum d1;
			d1.PushBack(10);
			d1.PushBack(20);
			Assert::AreEqual(d1.Size(), (size_t)2);
			Datum d2 = std::move(d1);
			Assert::AreEqual(d2.Size(), (size_t)2);
			Assert::AreEqual(d2.Front<std::int32_t>(), 10);
			Datum d3;
			d3 = std::move(d2);
			Assert::AreEqual(d3.Front<std::int32_t>(), 10);
			Assert::AreEqual(d3.Size(), (size_t)2);
			Assert::AreEqual(d3.Type(), DatumTypes::Integer);


		}
		TEST_METHOD(Equality)
		{
			{
				Datum d, d1, d2, d3, d4, d5;
				d.SetType(DatumTypes::Integer);
				d1.SetType(DatumTypes::Integer);
				d.PushBack(10);
				d.PushBack(20);
				d.PushBack(30);
				d1.PushBack(10);
				d1.PushBack(20);
				d1.PushBack(30);
				Assert::IsTrue(d == d1);
				Assert::IsTrue(d != d2);
				Datum s1, s2, s3;
				s1.SetType(DatumTypes::String);
				s2.SetType(DatumTypes::String);
				s1.PushBack("abc");
				s2.PushBack("abc");
				s3.PushBack("asdasdasd");
				Assert::IsTrue(s1 == s2);
				Assert::IsFalse(s2 == s3);
				Foo f1(10);
				Foo f2(10);
				RTTI* r1;
				RTTI* r2;
				RTTI* r3;
				r1 = &f1;
				r2 = &f1;
				r3 = &f2;
				d3.PushBack(r1);
				d4.PushBack(r2);
				d5.PushBack(r3);
				Assert::IsTrue(d3 == d4);
				Assert::IsFalse(d3 == d5);
			}

			{
				Datum d, d1, d2;
				d.SetType(DatumTypes::Integer);
				d.PushBack(5);
				Assert::IsTrue(d == 5);
				Assert::IsFalse(d == 6);
				d.PushBack(6);
				Assert::IsFalse(d == 6);
				Assert::IsTrue(d != 8);
			}
			{
				Datum d, d1, d2;
				d.SetType(DatumTypes::Float);
				d.PushBack(5.f);
				Assert::IsTrue(d == 5.f);
				Assert::IsFalse(d == 6.f);
				d.PushBack(6.f);
				Assert::IsFalse(d == 6.f);
				Assert::IsTrue(d != 8.f);
			}
			{
				Datum d, d1, d2;
				d.SetType(DatumTypes::Vector);
				glm::vec4 v(1.f);
				glm::vec4 v1(2.f);
				d.PushBack(v);
				Assert::IsTrue(d == v);
				Assert::IsFalse(d == v1);
				d.PushBack(v1);
				Assert::IsFalse(d == v1);
				Assert::IsTrue(d != v1);
			}
			{
				Datum d, d1, d2;
				d.SetType(DatumTypes::Matrix);
				glm::mat4 m(1.f);
				glm::mat4 m1(2.f);
				d.PushBack(m);
				Assert::IsTrue(d == m);
				Assert::IsFalse(d == m1);
				d.PushBack(m1);
				Assert::IsFalse(d == m1);
				Assert::IsTrue(d != m1);
			}
			{
				Datum d, d1, d2;
				d.SetType(DatumTypes::String);
				std::string a = "abc";
				std::string b = "abc123";
				d.PushBack(a);
				Assert::IsTrue(d == a);
				Assert::IsFalse(d == b);
				d.PushBack(b);
				Assert::IsFalse(d == b);
				Assert::IsTrue(d != b);
			}
			{
				Datum d, d1, d2;
				d.SetType(DatumTypes::Pointer);
				Foo f1(10);
				Foo f2(20);
				RTTI* r1 = &f1;
				RTTI* r2 = &f2;
				d.PushBack(r1);
				Assert::IsTrue(d == r1);
				Assert::IsFalse(d == r2);
				d.PushBack(r2);
				Assert::IsFalse(d == r2);
				Assert::IsTrue(d != r2);
			}
		}
		TEST_METHOD(Resize)
		{
			Datum d;
			Assert::AreEqual(d.Type(), DatumTypes::Unknown);
			Assert::AreEqual(d.Size(), (size_t)0);
			Assert::AreEqual(d.Capacity(), (size_t)0);
			d.SetType(DatumTypes::Integer);
			Assert::AreEqual(d.Type(), DatumTypes::Integer);
			d.Reserve(10);
			Assert::AreEqual(d.Size(), (size_t)0);
			Assert::AreEqual(d.Capacity(), (size_t)10);
			d.Resize(5);
			Assert::AreEqual(d.Size(), (size_t)5);
			Assert::AreEqual(d.Capacity(), (size_t)5);
			d.Resize(15);
			Assert::AreEqual(d.Size(), (size_t)15);
			Assert::AreEqual(d.Capacity(), (size_t)15);
			d.PushBack(10);
			d.PushBack(10);
			d.PushBack(10);
			d.PushBack(10);
			d.PushBack(10);
			d.Resize(2);
			Assert::AreEqual(d.Size(), (size_t)2);
			Assert::AreEqual(d.Capacity(), (size_t)2);
			Datum d1;
			Assert::AreEqual(d1.Type(), DatumTypes::Unknown);
			Assert::AreEqual(d1.Size(), (size_t)0);
			Assert::AreEqual(d1.Capacity(), (size_t)0);
			d1.SetType(DatumTypes::String);
			d1.Resize(5);

		}

		TEST_METHOD(PushBack)
		{
			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				d.PushBack(10);
				Assert::AreEqual(d.Type(), DatumTypes::Integer);
				Assert::AreEqual(d.Size(), (size_t)1);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				d.PushBack(20);
				Assert::AreEqual(d.Size(), (size_t)2);
				Assert::ExpectException<std::runtime_error>([&d] {d.PushBack(10.f); });
			}

			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				d.PushBack(10.f);
				Assert::AreEqual(d.Type(), DatumTypes::Float);
				Assert::AreEqual(d.Size(), (size_t)1);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				d.PushBack(20.f);
				Assert::AreEqual(d.Size(), (size_t)2);
				Assert::ExpectException<std::runtime_error>([&d] {d.PushBack(10); });
			}

			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				glm::vec4 v1;
				d.PushBack(v1);
				Assert::AreEqual(d.Type(), DatumTypes::Vector);
				Assert::AreEqual(d.Size(), (size_t)1);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				glm::vec4 v2;
				d.PushBack(v2);
				Assert::AreEqual(d.Size(), (size_t)2);
				glm::mat4 m;
				Assert::ExpectException<std::runtime_error>([&d, &m] {d.PushBack(m); });
			}

			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				glm::mat4 m1;
				d.PushBack(m1);
				Assert::AreEqual(d.Type(), DatumTypes::Matrix);
				Assert::AreEqual(d.Size(), (size_t)1);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				glm::mat4 m2;
				d.PushBack(m2);
				Assert::AreEqual(d.Size(), (size_t)2);
				glm::vec4 v;
				Assert::ExpectException<std::runtime_error>([&d, &v] {d.PushBack(v); });
			}

			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				std::string s1 = "dashk";
				d.PushBack(s1);
				Assert::AreEqual(d.Type(), DatumTypes::String);
				Assert::AreEqual(d.Size(), (size_t)1);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				std::string s2 = "dashk";
				d.PushBack(s2);
				Assert::AreEqual(d.Size(), (size_t)2);
				Foo f2(10);
				RTTI* r = &f2;
				Assert::ExpectException<std::runtime_error>([&d, &r] {d.PushBack(r); });
				d.PushBack("abc");
				Assert::AreEqual(d.Size(), (size_t)3);

			}

			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				Foo f1(10);
				RTTI* r;
				r = &f1;
				d.PushBack(r);
				Assert::AreEqual(d.Type(), DatumTypes::Pointer);
				Assert::AreEqual(d.Size(), (size_t)1);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				std::string s = "";
				Assert::ExpectException<std::runtime_error>([&d, &s] {d.PushBack(s); });
				Assert::ExpectException<std::runtime_error>([&d] {d.PushBack("asds"); });
			}
		}

		TEST_METHOD(Set)
		{
			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				Assert::ExpectException<std::out_of_range>([&d] {d.Set(10, 20); });
				d.Set(10);
				Assert::AreEqual(d.Type(), DatumTypes::Integer);
				Assert::AreEqual(d.Size(), (size_t)1);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				Assert::ExpectException<std::out_of_range>([&d] {d.Set(20, 20); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Set(20.f); });
			}
			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				Assert::ExpectException<std::out_of_range>([&d] {d.Set(10.f, 20); });
				d.Set(10.f);
				Assert::AreEqual(d.Type(), DatumTypes::Float);
				Assert::AreEqual(d.Size(), (size_t)1);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				Assert::ExpectException<std::out_of_range>([&d] {d.Set(20, 20); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Set(20); });
			}
			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				std::string a = "";
				Assert::ExpectException<std::out_of_range>([&d, &a] {d.Set(a, 20); });
				d.Set(a);
				Assert::AreEqual(d.Type(), DatumTypes::String);
				Assert::AreEqual(d.Size(), (size_t)1);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				Assert::ExpectException<std::out_of_range>([&d] {d.Set(20, 20); });
				Assert::ExpectException<std::runtime_error>([&d] {Foo f(10); RTTI* r = &f; d.Set(r); });
			}
			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				glm::vec4 v;
				Assert::ExpectException<std::out_of_range>([&d, &v] {d.Set(v, 20); });

				d.Set(v);
				Assert::AreEqual(d.Type(), DatumTypes::Vector);
				Assert::AreEqual(d.Size(), (size_t)1);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				Assert::ExpectException<std::out_of_range>([&d] {d.Set(20, 20); });
				Assert::ExpectException<std::runtime_error>([&d] {glm::mat4 m; d.Set(m); });
			}
			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				glm::mat4 m;
				Assert::ExpectException<std::out_of_range>([&d, &m] {d.Set(m, 20); });

				d.Set(m);
				Assert::AreEqual(d.Type(), DatumTypes::Matrix);
				Assert::AreEqual(d.Size(), (size_t)1);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				Assert::ExpectException<std::out_of_range>([&d] {d.Set(20, 20); });
				Assert::ExpectException<std::runtime_error>([&d] {glm::vec4 v; d.Set(v); });
			}
			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				RTTI* r;
				Foo f1(10);
				r = &f1;
				Assert::ExpectException<std::out_of_range>([&d, &r] {d.Set(r, 20); });
				d.Set(r);
				Assert::AreEqual(d.Type(), DatumTypes::Pointer);
				Assert::AreEqual(d.Size(), (size_t)1);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				Assert::ExpectException<std::out_of_range>([&d] {d.Set(20, 20); });
				Assert::ExpectException<std::runtime_error>([&d] {std::string a = ""; d.Set(a); });
			}
		}

		TEST_METHOD(Get)
		{
			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				d.PushBack(10);
				d.PushBack(20);
				Assert::AreEqual(d.Type(), DatumTypes::Integer);
				Assert::AreEqual(d.Size(), (size_t)2);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				Assert::AreEqual(d.Get<int>(0), 10);
				Assert::AreEqual(d.Get<int>(1), 20);
				Assert::ExpectException<std::out_of_range>([&d] {d.Get<int>(20); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Get<float>(0); });
				const Datum d1 = d;
				Assert::AreEqual(d1.Type(), DatumTypes::Integer);
				Assert::AreEqual(d1.Size(), (size_t)2);
				Assert::AreEqual(d1.Capacity(), (size_t)10);
				Assert::AreEqual(d1.Get<int>(0), 10);
				Assert::AreEqual(d1.Get<int>(1), 20);
				Assert::ExpectException<std::out_of_range>([&d1] {d1.Get<int>(20); });
				Assert::ExpectException<std::runtime_error>([&d1] {d1.Get<float>(0); });

			}
			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				d.PushBack(10.f);
				d.PushBack(20.f);
				Assert::AreEqual(d.Type(), DatumTypes::Float);
				Assert::AreEqual(d.Size(), (size_t)2);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				Assert::AreEqual(d.Get<float>(0), 10.f);
				Assert::AreEqual(d.Get<float>(1), 20.f);
				Assert::ExpectException<std::out_of_range>([&d] {d.Get<float>(20); });
				Assert::ExpectException<std::runtime_error>([&d] {d.Get<int>(0); });
				const Datum d1 = d;
				Assert::AreEqual(d1.Type(), DatumTypes::Float);
				Assert::AreEqual(d1.Size(), (size_t)2);
				Assert::AreEqual(d1.Capacity(), (size_t)10);
				Assert::AreEqual(d1.Get<float>(0), 10.f);
				Assert::AreEqual(d1.Get<float>(1), 20.f);
				Assert::ExpectException<std::out_of_range>([&d1] {d1.Get<float>(20); });
				Assert::ExpectException<std::runtime_error>([&d1] {d1.Get<int>(0); });
			}
			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				glm::vec4 v;
				glm::vec4 v1;
				d.PushBack(v);
				d.PushBack(v1);
				Assert::AreEqual(d.Type(), DatumTypes::Vector);
				Assert::AreEqual(d.Size(), (size_t)2);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				Assert::AreEqual(d.Get<glm::vec4>(0), v);
				Assert::AreEqual(d.Get<glm::vec4>(1), v1);
				Assert::ExpectException<std::out_of_range>([&d] {d.Get<glm::vec4>(20); });
				Assert::ExpectException<std::runtime_error>([&d] { d.Get<glm::mat4>(0); });
				const Datum d1 = d;
				Assert::AreEqual(d1.Type(), DatumTypes::Vector);
				Assert::AreEqual(d1.Size(), (size_t)2);
				Assert::AreEqual(d1.Capacity(), (size_t)10);
				Assert::AreEqual(d1.Get<glm::vec4>(0), v);
				Assert::AreEqual(d1.Get<glm::vec4>(1), v1);
				Assert::ExpectException<std::out_of_range>([&d1] {d1.Get<glm::vec4>(20); });
				Assert::ExpectException<std::runtime_error>([&d1] {d1.Get<glm::mat4>(0); });
			}
			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				glm::mat4 m;
				glm::mat4 m1;
				d.PushBack(m);
				d.PushBack(m1);
				Assert::AreEqual(d.Type(), DatumTypes::Matrix);
				Assert::AreEqual(d.Size(), (size_t)2);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				Assert::AreEqual(d.Get<glm::mat4>(0), m);
				Assert::AreEqual(d.Get<glm::mat4>(1), m1);
				Assert::ExpectException<std::out_of_range>([&d] {d.Get<glm::mat4>(20); });
				Assert::ExpectException<std::runtime_error>([&d] { d.Get<glm::vec4>(0); });
				const Datum d1 = d;
				Assert::AreEqual(d1.Type(), DatumTypes::Matrix);
				Assert::AreEqual(d1.Size(), (size_t)2);
				Assert::AreEqual(d1.Capacity(), (size_t)10);
				Assert::AreEqual(d1.Get<glm::mat4>(0), m);
				Assert::AreEqual(d1.Get<glm::mat4>(1), m1);
				Assert::ExpectException<std::out_of_range>([&d1] {d1.Get<glm::mat4>(20); });
				Assert::ExpectException<std::runtime_error>([&d1] {d1.Get<glm::vec4>(0); });
			}
			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				std::string a;
				std::string a1 = "abc";
				d.PushBack(a);
				d.PushBack(a1);
				Assert::AreEqual(d.Type(), DatumTypes::String);
				Assert::AreEqual(d.Size(), (size_t)2);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				Foo f1(20);
				RTTI* r = &f1;
				Assert::AreEqual(d.Get<std::string>(0), a);
				Assert::AreEqual(d.Get<std::string>(1), a1);
				Assert::ExpectException<std::out_of_range>([&d] {d.Get<std::string>(20); });
				Assert::ExpectException<std::runtime_error>([&d, &r] { d.Get<RTTI*>(0); });
				const Datum d1 = d;
				Assert::AreEqual(d1.Type(), DatumTypes::String);
				Assert::AreEqual(d1.Size(), (size_t)2);
				Assert::AreEqual(d1.Capacity(), (size_t)10);
				Assert::AreEqual(d1.Get<std::string>(0), a);
				Assert::AreEqual(d1.Get<std::string>(1), a1);
				Assert::ExpectException<std::out_of_range>([&d1] {d1.Get<std::string>(20); });
				Assert::ExpectException<std::runtime_error>([&d1, &r] { d1.Get<RTTI*>(0); });
			}
			{
				Datum d;
				Assert::AreEqual(d.Type(), DatumTypes::Unknown);
				Assert::AreEqual(d.Size(), (size_t)0);
				Assert::AreEqual(d.Capacity(), (size_t)0);
				Foo f1(20);
				RTTI* r = &f1;
				d.PushBack(r);
				d.PushBack(r);
				Assert::AreEqual(d.Type(), DatumTypes::Pointer);
				Assert::AreEqual(d.Size(), (size_t)2);
				Assert::AreEqual(d.Capacity(), (size_t)10);
				std::string a = "";
				Assert::AreEqual(d.Get<RTTI*>(0), r);
				Assert::ExpectException<std::out_of_range>([&d] {d.Get<RTTI*>(20); });
				Assert::ExpectException<std::runtime_error>([&d, &a] { d.Get<std::string>(0); });
				const Datum d1 = d;
				Assert::AreEqual(d1.Type(), DatumTypes::Pointer);
				Assert::AreEqual(d1.Size(), (size_t)2);
				Assert::AreEqual(d1.Capacity(), (size_t)10);
				Assert::AreEqual(d1.Get<RTTI*>(0), r);
				Assert::ExpectException<std::out_of_range>([&d1] {d1.Get<RTTI*>(20); });
				Assert::ExpectException<std::runtime_error>([&d1, &a] { d1.Get<std::string>(0); });
			}
		}

		TEST_METHOD(ToString)
		{
			{
				Datum d;
				d.SetType(DatumTypes::Integer);
				d.PushBack(10);
				std::string a = "10";
				Assert::AreEqual(a, d.ToString(0));
			}
			{
				Datum d;
				d.SetType(DatumTypes::Float);
				d.PushBack(10.f);
				std::string a = "10.000000";
				Assert::AreEqual(a, d.ToString(0));
			}

			{
				Datum d;
				d.SetType(DatumTypes::String);
				std::string a = "10.000000";
				d.PushBack(a);
				Assert::AreEqual(a, d.ToString(0));
			}

			{
				Datum d;
				d.SetType(DatumTypes::Vector);
				glm::vec4 v(1.f);
				d.PushBack(v);
				std::string a = "vec4(1.000000, 1.000000, 1.000000, 1.000000)";
				Assert::AreEqual(a, d.ToString(0));
			}

			{
				Datum d;
				d.SetType(DatumTypes::Matrix);
				glm::mat4 m(1.f);
				d.PushBack(m);
				std::string a = "mat4x4((1.000000, 0.000000, 0.000000, 0.000000), (0.000000, 1.000000, 0.000000, 0.000000), (0.000000, 0.000000, 1.000000, 0.000000), (0.000000, 0.000000, 0.000000, 1.000000))";
				Assert::AreEqual(a, d.ToString(0));
			}

			{
				Datum d;
				Assert::ExpectException<std::runtime_error>([&d] {d.ToString(); });

			}
		}

		TEST_METHOD(SetFromString)
		{
			{
				Datum d;
				d.SetType(DatumTypes::Integer);
				d.Reserve(10);
				d.SetFromString("5", 0);
				Assert::AreEqual(d.Front<std::int32_t>(), 5);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Float);
				d.Reserve(10);
				d.SetFromString("5.f", 0);
				Assert::AreEqual(d.Front<float>(), 5.f);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Vector);
				d.Reserve(10);
				glm::vec4 v(1.0f);
				d.SetFromString(glm::to_string(v), 0);
				Assert::AreEqual(d.Front<glm::vec4>(), v);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Matrix);
				d.Reserve(10);
				glm::mat4 m(1.0f);
				d.SetFromString(glm::to_string(m), 0);
				Assert::AreEqual(d.Front<glm::mat4>(), m);
			}

			{
				Datum d;
				d.SetType(DatumTypes::String);
				d.Reserve(10);
				std::string a = "abc";
				d.SetFromString(a, 0);
				Assert::AreEqual(d.Front<std::string>(), a);
			}
			{
				Datum d;
				std::string a = ";";
				Assert::ExpectException<std::runtime_error>([&d, &a] {d.SetFromString(a); });
			}

		}

		TEST_METHOD(PushBackFromString)
		{
			Datum d;
			d.SetType(DatumTypes::Integer);
			d.Reserve(10);
			Assert::AreEqual(d.Size(), (std::size_t)0);
			d.PushBackFromString("10");
			Assert::AreEqual(d.Front<std::int32_t>(), 10);
		}

		TEST_METHOD(SetStorage)
		{
			Datum d;
			d.SetType(DatumTypes::Integer);
			d.Reserve(10);
			Assert::AreEqual(d.Size(), (std::size_t)0);
			Assert::AreEqual(d.Capacity(), (std::size_t)10);
			std::int32_t a[3] = { 0,1,2 };
			d.SetStorage(a, 3);
			d.Set(10, 1);
			Assert::AreEqual(d.Size(), (std::size_t)3);
			Assert::AreEqual(d.Capacity(), (std::size_t)3);
			Assert::AreEqual(d.Front<std::int32_t>(), 0);
			std::string s[3];
			d.SetStorage(s, 3);
			Assert::AreEqual(d.Type(), DatumTypes::String);
			{
				Datum d1;
				d1.SetType(DatumTypes::String);
				std::string c = "";
				d1.PushBack(c);
				Assert::ExpectException<std::runtime_error>([&d1, &s] {d1.SetStorage(s, 3); });
			}

			{
				Datum d1;
				d1.SetType(DatumTypes::Vector);
				glm::vec4 v(1.0f);
				glm::vec4 v1[3];
				d1.PushBack(v);
				Assert::ExpectException<std::runtime_error>([&d1, &v1] {d1.SetStorage(v1, 3); });
			}
			{
				Datum d1;
				d1.SetType(DatumTypes::Matrix);
				glm::mat4 v(1.0f);
				glm::mat4 v1[3];
				d1.PushBack(v);
				Assert::ExpectException<std::runtime_error>([&d1, &v1] {d1.SetStorage(v1, 3); });
			}
			{
				Datum d1;
				d1.SetType(DatumTypes::Pointer);
				Foo f1{ 10 };
				RTTI* r1[3];
				RTTI* r = &f1;
				d1.PushBack(r);
				Assert::ExpectException<std::runtime_error>([&d1, &r1] {d1.SetStorage(r1, 3); });
			}
		}
		TEST_METHOD(Remove)
		{
			{
				Datum d1;
				d1.SetType(DatumTypes::Integer);
				d1.Reserve(10);
				Assert::AreEqual(d1.Size(), (std::size_t)0);
				Assert::AreEqual(d1.Capacity(), (std::size_t)10);
				d1.PushBack(10);
				d1.PushBackFromString("20");
				Assert::AreEqual(d1.Size(), (std::size_t)2);
				Assert::AreEqual(d1.Remove(20), true);
				Assert::AreEqual(d1.Size(), (std::size_t)1);
				Assert::AreEqual(d1.Remove(30), false);
				Assert::AreEqual(d1.Size(), (std::size_t)1);
			}


			{
				Datum d1;
				d1.SetType(DatumTypes::Float);
				d1.Reserve(10);
				Assert::AreEqual(d1.Size(), (std::size_t)0);
				Assert::AreEqual(d1.Capacity(), (std::size_t)10);
				d1.PushBack(10.f);
				d1.PushBackFromString("20.f");
				Assert::AreEqual(d1.Size(), (std::size_t)2);
				Assert::AreEqual(d1.Remove(20.f), true);
				Assert::AreEqual(d1.Size(), (std::size_t)1);
				Assert::AreEqual(d1.Remove(30.f), false);
				Assert::AreEqual(d1.Size(), (std::size_t)1);
			}

			{
				Datum d1;
				d1.SetType(DatumTypes::String);
				d1.Reserve(10);
				Assert::AreEqual(d1.Size(), (std::size_t)0);
				Assert::AreEqual(d1.Capacity(), (std::size_t)10);
				std::string a = "abc";
				d1.PushBack(a);
				d1.PushBackFromString("abc1");
				Assert::AreEqual(d1.Size(), (std::size_t)2);
				Assert::AreEqual(d1.Remove("abc1"), true);
				Assert::AreEqual(d1.Size(), (std::size_t)1);
				Assert::AreEqual(d1.Remove("dasdsa"), false);
				Assert::AreEqual(d1.Size(), (std::size_t)1);
			}

			{
				Datum d1;
				d1.SetType(DatumTypes::Matrix);
				d1.Reserve(10);
				Assert::AreEqual(d1.Size(), (std::size_t)0);
				Assert::AreEqual(d1.Capacity(), (std::size_t)10);
				glm::mat4 a(1);
				glm::mat4 b(2);
				glm::mat4 b1(22);
				d1.PushBack(a);
				d1.PushBack(b);
				Assert::AreEqual(d1.Size(), (std::size_t)2);
				Assert::AreEqual(d1.Remove(a), true);
				Assert::AreEqual(d1.Size(), (std::size_t)1);
				Assert::AreEqual(d1.Remove(b1), false);
				Assert::AreEqual(d1.Size(), (std::size_t)1);
			}
			{
				Datum d1;
				d1.SetType(DatumTypes::Vector);
				d1.Reserve(10);
				Assert::AreEqual(d1.Size(), (std::size_t)0);
				Assert::AreEqual(d1.Capacity(), (std::size_t)10);
				glm::vec4 a(1);
				glm::vec4 b(2);
				glm::vec4 b1(22);
				d1.PushBack(a);
				d1.PushBack(b);
				Assert::AreEqual(d1.Size(), (std::size_t)2);
				Assert::AreEqual(d1.Remove(a), true);
				Assert::AreEqual(d1.Size(), (std::size_t)1);
				Assert::AreEqual(d1.Remove(b1), false);
				Assert::AreEqual(d1.Size(), (std::size_t)1);
			}

			{
				Datum d1;
				d1.SetType(DatumTypes::Pointer);
				d1.Reserve(10);
				Assert::AreEqual(d1.Size(), (std::size_t)0);
				Assert::AreEqual(d1.Capacity(), (std::size_t)10);
				Foo f1(10);
				Foo f2(100);
				Foo f3(1000);
				RTTI* r = &f1;
				RTTI* r1 = &f2;
				RTTI* r2 = &f3;
				d1.PushBack(r);
				d1.PushBack(r1);
				Assert::AreEqual(d1.Size(), (std::size_t)2);
				Assert::AreEqual(d1.Remove(r), true);
				Assert::AreEqual(d1.Size(), (std::size_t)1);
				Assert::AreEqual(d1.Remove(r2), false);
				Assert::AreEqual(d1.Size(), (std::size_t)1);
				Assert::ExpectException<std::out_of_range>([&d1] {d1.RemoveAt(3); });
			}
		}

		TEST_METHOD(Find)
		{
			{
				Datum d1;
				d1.SetType(DatumTypes::Integer);
				d1.Reserve(10);
				Assert::AreEqual(d1.Size(), (std::size_t)0);
				Assert::AreEqual(d1.Capacity(), (std::size_t)10);
				d1.PushBack(10);
				d1.PushBackFromString("20");
				Assert::AreEqual(d1.Size(), (std::size_t)2);
				Assert::AreEqual(d1.Find(20).first, true);
				Assert::AreEqual(d1.Find(30).first, false);
			}


			{
				Datum d1;
				d1.SetType(DatumTypes::Float);
				d1.Reserve(10);
				Assert::AreEqual(d1.Size(), (std::size_t)0);
				Assert::AreEqual(d1.Capacity(), (std::size_t)10);
				d1.PushBack(10.f);
				d1.PushBackFromString("20.f");
				Assert::AreEqual(d1.Size(), (std::size_t)2);
				Assert::AreEqual(d1.Find(20.f).first, true);
				Assert::AreEqual(d1.Find(30.f).first, false);

			}

			{
				Datum d1;
				d1.SetType(DatumTypes::String);
				d1.Reserve(10);
				Assert::AreEqual(d1.Size(), (std::size_t)0);
				Assert::AreEqual(d1.Capacity(), (std::size_t)10);
				std::string a = "abc";
				d1.PushBack(a);
				d1.PushBackFromString("abc1");
				Assert::AreEqual(d1.Size(), (std::size_t)2);
				Assert::AreEqual(d1.Find("abc1").first, true);
				Assert::AreEqual(d1.Find("dasdsa").first, false);

			}

			{
				Datum d1;
				d1.SetType(DatumTypes::Matrix);
				d1.Reserve(10);
				Assert::AreEqual(d1.Size(), (std::size_t)0);
				Assert::AreEqual(d1.Capacity(), (std::size_t)10);
				glm::mat4 a(1);
				glm::mat4 b(2);
				glm::mat4 b1(22);
				d1.PushBack(a);
				d1.PushBack(b);
				Assert::AreEqual(d1.Size(), (std::size_t)2);
				Assert::AreEqual(d1.Find(a).first, true);
				Assert::AreEqual(d1.Find(b1).first, false);

			}
			{
				Datum d1;
				d1.SetType(DatumTypes::Vector);
				d1.Reserve(10);
				Assert::AreEqual(d1.Size(), (std::size_t)0);
				Assert::AreEqual(d1.Capacity(), (std::size_t)10);
				glm::vec4 a(1);
				glm::vec4 b(2);
				glm::vec4 b1(22);
				d1.PushBack(a);
				d1.PushBack(b);
				Assert::AreEqual(d1.Size(), (std::size_t)2);
				Assert::AreEqual(d1.Find(a).first, true);
				Assert::AreEqual(d1.Find(b1).first, false);
			}

			{
				Datum d1;
				d1.SetType(DatumTypes::Pointer);
				d1.Reserve(10);
				Assert::AreEqual(d1.Size(), (std::size_t)0);
				Assert::AreEqual(d1.Capacity(), (std::size_t)10);
				Foo f1(10);
				Foo f2(100);
				Foo f3(1000);
				RTTI* r = &f1;
				RTTI* r1 = &f2;
				RTTI* r2 = &f3;
				d1.PushBack(r);
				d1.PushBack(r1);
				Assert::AreEqual(d1.Size(), (std::size_t)2);
				Assert::AreEqual(d1.Find(r).first, true);
				Assert::AreEqual(d1.Find(r2).first, false);
			}
		}





	private:
		static _CrtMemState _startMemState;

	};
	_CrtMemState DatumTests::_startMemState;


}




