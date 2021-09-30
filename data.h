#pragma once
#ifndef STOCKAPP_DATA
#define STOCKAPP_DATA

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include "string.h"

using namespace std;

struct Time
{
	int Y;//�� 
	int M;//�� 
	int D;//�� 
	int h;//ʱ 
	int m;//�� 
	int s;//�� 
	Time()
	{
		time_t _t=time(NULL);
		tm *t=localtime(&_t);
		Y=t->tm_year+1900;
		M=t->tm_mon+1;
		D=t->tm_mday;
		h=t->tm_hour;
		m=t->tm_min;
		s=t->tm_sec;	
	}

	string parse()
	{
		char temp[64];
		sprintf(temp,"%d/%d/%d %02d:%02d:%02d",this->Y,this->M,this->D,this->h,this->m,this->s);
		return temp;
	}

};

//�ֲ���Ϣ
struct Holdshare{
    string code;
    string name;
    int num;
    double price;//���׾���
    
    //����find����
    bool operator == (const string &code){
        return (this->code == code);
    }  
};

struct Entrust//ί����� 
{
	string username;//ί�����û��� 
    string code;
	double price;//ί�м�
	bool isbuy;//�Ƿ�Ϊ����
	int num;//�������ԡ��ɡ�Ϊ��λ 
	Time time;//����ʱ�� 

};

class Stock
{
    public:
    /* data */

    string name;
    string code;
    float nowPrice;
    float increaseRate;
    float increaseValue;
    float buyPrice;
    float sellPrice;
    float turnoverRate;
    unsigned long int totolHand;
    float totalAmount;
    float circMarketValue;
    float peRatio;
    float pbRatio;

    vector <Entrust> entrust;//ί�н��� 
    void setStockData(vector<string> ret) {
        this->name = ret[1];
        this->code = ret[2];
        this->nowPrice = stof(ret[3]);
        this->increaseRate = stof(ret[32]);
        this->increaseValue = stof(ret[31]);
        this->buyPrice = stof(ret[9]);
        this->sellPrice = stof(ret[19]);
        this->turnoverRate = stof(ret[38]);
        this->totolHand = stoi(ret[36]);
        this->totalAmount = stof(ret[57]);
        this->circMarketValue = stof(ret[44]);
        this->peRatio = stof(ret[39]);
        this->pbRatio = stof(ret[46]);
    } 
    //����find����
    bool operator == (const string &code){
        return (this->code == code);
    }  
};

class User
{
	public:
	string username;
	string pass;
	User(){username="";}
	User(string name,string pass)	{ username=name;setpass(pass);}//�����û� 
	void reg(string name,string pass){username=name;setpass(pass);}//�����û� 
	void setpass(string _pass){ pass=_pass;}
	bool verify(string _pass){if(pass==_pass) return true; else return false;}//��֤�û������� 
};


extern vector<Stock> stocks;
extern User actuser;//ȫ�ֱ��� ��ʾ��ǰ��¼���û�
extern vector<User> users; //�û����� 
extern map<string, vector<Entrust>> transactions;// ����
extern map<string, vector<Holdshare>> holdshares;// �ֲ�
extern vector<string> urls; //���ʹ�Ʊ��Ϣ��API



namespace opt {
    namespace stock
    {
        
        void getStocksData(void);
        vector<string> requestData(string strurl, string splitstr);
        int  updateHoldshare(Entrust entrust, string stockName);    
        void entrust(int index);
        void stockEntrustRecord(Stock stock, int displayLine);
        vector<Stock>::iterator findStockInVector(string code);
        vector<Holdshare>::iterator findHoldshareInVector(string code);
    }
    namespace cmp 
    {
        bool time(Time a,Time b);
        bool entrust(Entrust a, Entrust b);
    }
    namespace test
    {
        string GetLineFromCin();
    }
   
}
#endif