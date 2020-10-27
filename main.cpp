#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <algorithm>
using namespace std;
const double eps = 1e-8;
/****************************************************************
功能：返回两个字符串的重复长度。
Exmaple:
	Input:  "abcd"、"abf"  
	output: 2
****************************************************************/
int getCommonLen(std::string str1,std::string str2)
{
	int i;
	for(i=0;i<str1.size()&&i<str2.size();i++)
	{
		if(str1[i] != str2[i])
			break;
	}
	return i;
}


/****************************************************************
功能：写一个函数，找出一个字符串中最长的连续重复子串。
Exmaple:
	Input: abcdefgabcfg    
	output: abc
原理：
	substr0  abcdefgabcfg
	substr1   bcdefgabcfg
	substr2    cdefgabcfg
	substr3     defgabcfg
	substr4      efgabcfg
	substr5       fgabcfg
	substr6        gabcfg
	substr7         abcfg
	substr8          bcfg
	substr9           cfg
	substr10           fg
	substr11            g
	先排序，再循环更新最大重复子字符串
****************************************************************/
std::string fun(const string& str)
{
	std::cout<<str<<std::endl;
	std::vector<std::string> substrs;  
	int maxLen = 1;
	std::string substr;
	int len = str.length();
	
	//将子字符串存放到动态数组
	for(int i=0; i<len; ++i)
		substrs.push_back(str.substr(i,len-i));
	//字符串排序
	std::sort(substrs.begin(),substrs.end());
	//循环更新
	for(int i=0;i<substrs.size()-1;i++)
	{
		int commonLen = getCommonLen(substrs[i],substrs[i+1]);
		if(commonLen > maxLen){
			maxLen = commonLen;
			substr = substrs[i].substr(0,maxLen);
		}
	}
	//返回最大重复子字符串
	return substr;
}

// 代码题2

/****************************************************************
功能：点和向量结构体。
****************************************************************/
struct PointAndVector
{
    double x, y;
};
/****************************************************************
功能：写一个函数，返回平面上两个向量的叉积。
Exmaple:
	Input:  A(2,3)、B(2,4)  
	output: 2
原理：
	向量叉乘公式
****************************************************************/
double xmult(PointAndVector A, PointAndVector B) { 
	return A.x * B.y - B.x * A.y ;
}

/****************************************************************
功能：写一个函数，判断同一平面的两个三角形是否相交。
Exmaple:
	Input: 三角形A和B
		P[0][0].x=0,P[0][0].y=0,P[0][1].x=2,P[0][1].y=0,P[0][2].x=0,P[0][2].x=2,P[0][3].x=P[0][0].x,P[0][3].y=P[0][0].y; 
		P[1][0].x=0,P[1][0].y=0,P[1][1].x=2,P[0][1].y=0,P[1][2].x=2,P[0][2].x=2,P[1][3].x=P[1][0].x,P[1][3].y=P[1][0].y;
	output: true
原理：
	两个三角形各拿出一条边，共有9种组合，判断每种组合的两条边是否相交，出现一对边相交则两个三角形相交
****************************************************************/
bool isIntersect(PointAndVector points[2][4])
{
    bool intersect = false;
	for(int i = 0;i<3 && !intersect;i++)
	{
		for(int j = 0;j<3 && !intersect; j++)
		{
			/*第一个三角形的第i条边与第二个三角形的第j调边是否相交；
			线段AB与线段CD相交的充要条件是直线AB与线段CD相交，并且直线CD与线段AB相交；
			判断直线AB与线段CD相交只需要判断C、D两点分别在直线AB的两边，即AB×AC与AB×AD异号；
			判断直线CD与线段AB相交同理。
			*/
			PointAndVector AB,AC,AD;
			PointAndVector CD,CA,CB;
			AB.x = points[0][i+1].x - points[0][i].x;
			AB.y = points[0][i+1].y - points[0][i].y;
			AC.x = points[1][j].x - points[0][i].x;
			AC.y = points[1][j].y - points[0][i].y;
			AD.x = points[1][j+1].x - points[0][i].x;
			AD.y = points[1][j+1].y - points[0][i].y;
			
			CD.x = points[1][j+1].x - points[1][j].x;
			CD.y = points[1][j+1].y - points[1][j].y;
			CA.x = -AC.x;
			CA.y = -AC.y;
			CB.x = points[0][i+1].x - points[1][j].x;
			CB.y = points[0][i+1].y - points[1][j].y;
			
			if (xmult(AB, AC) * xmult(AB, AD) < eps && xmult(CD, CA) * xmult(CD, CB) < eps)
			{
				intersect = true ;
			}
		}
	}
	return intersect;
}
int main(){
	// 代码习题1测试
	std::string testString = "abcdefgabcfg";
	std::string maxSubStr = fun(testString);
	std::cout<<maxSubStr<<std::endl;
	
	//代码习题2测试
	PointAndVector P[2][4];
	P[0][0].x=0,P[0][0].y=0,P[0][1].x=2,P[0][1].y=0,P[0][2].x=0,P[0][2].x=2,P[0][3].x=P[0][0].x,P[0][3].y=P[0][0].y; 
	P[1][0].x=0,P[1][0].y=0,P[1][1].x=2,P[0][1].y=0,P[1][2].x=2,P[0][2].x=2,P[1][3].x=P[1][0].x,P[1][3].y=P[1][0].y;
	bool intersect = isIntersect(P);
	if(intersect)
	{
		std::cout<<"两三角形相交"<<std::endl;
	}else{
		std::cout<<"两三角形不相交"<<std::endl;
	}
	
	return 0;
}