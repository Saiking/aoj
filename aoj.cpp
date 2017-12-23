// aoj1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//


#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
namespace Domain
{
	////result
	class Result
	{
		bool ok;
	public:
		Result(bool ok=false):ok(ok){}
		bool disp() {	return  ok ;}
	};

	////circle 
	class Circle
	{
		int x, y,r;
		bool over(int b, int r, int m){	return (b+r > m) ? true : false;}
		bool under(int b, int r){	return (b-r < 0) ? true : false;}
	public:
		Circle(int x=0, int y=0 ,int r=0) :x(x), y(y),r(r) {}
		bool error(int W, int H)
		{
			if (!under(x, r) && !under(y, r) && !over(x, r, W) && !over(y, r, H)) return false;
			return true;
		}
	};
	////rectangle
	class Rect
	{
		int W, H;
	public :
		Rect(int w=0, int h=0) :W(w), H(h) {}
		template <typename T,typename U>
		void  over(T& shape,U& result) {
			result=shape.error(W, H);
		}
	};

}
using namespace Domain;
namespace InterfaceAdapter
{
	namespace Presenter
	{	
		////display
		class ResultDisp
		{
			static string msg[2];
		public:
			string disp(Result result) {	return  msg[result.disp()] ;}
		};
		string ResultDisp::msg[2]= { "Yes","No" };
	}
	namespace Controller
	{	
		//// input rect circle parameter
		class RectInput
		{
		public :
			void inp(Rect& rect,Circle& circle)
			{
				int w,h,x,y,r;
				cin >> w>>h>> x>>y>>r;
				Rect rec(w,h);
				Circle cir(x,y,r);
				rect=rec;
				circle =cir;
			}
		};
	}

}
using namespace Domain;
using namespace InterfaceAdapter;

namespace UseCase
{

	namespace InputPort
	{

		////interface input
		class Input
		{
		public :
			template <typename X>
			static void inp(X shapeIn,Rect& shape1,Circle& shape2)
			{
				shapeIn.inp(shape1,shape2);
			}
		};
	}
	namespace OutputPort
	{

		////interface display
		class Display
		{
		public:
			template <typename U,typename V>
			static void disp(U& result,V& dispType) { 
				cout << dispType.disp(result) << endl;
			}
		};
	}
	using namespace InputPort;
	using namespace OutputPort;
	using namespace InterfaceAdapter::Presenter;
	using namespace InterfaceAdapter::Controller;
	class CaseOver
	{
	public:


		////use case
		static void check()
		{
			////input rect circle parameter
			RectInput rectInput;
			Rect rect;
			Circle circle;
			Input::inp(rectInput,rect,circle);
			//check over
			Result result;
			rect.over(circle,result);

			//disp result
			ResultDisp resultDisp;
			Display::disp(result,resultDisp);
		}
	};
}
using namespace UseCase;
int main()
{
	CaseOver::check();
	return 0;

}

