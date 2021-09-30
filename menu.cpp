#include "menu.h"
#include "data.h"
#include "output.h"
#include "lib/winconsole.h"
#include <algorithm>
#include <iostream>


using namespace std;

void Menu::welcome()
{

	printWelcomeTable(0);
	system("pause");
	parimary();	

}

void Menu::parimary()
{	
	int displayLine;
	string select;
	displayLine = printParimaryMenu(0);
	cin >> select;
	if     (select == "1") quotes();
	else if(select == "2") trade(); 
	else if(select == "3") record(); 
	else if(select == "4") myhold(); 
	else if(select == "5") system("exit");
	else error();

}

void Menu::quotes()
{
	bool keep_running = true;
	string input;
	int nextLine = 0;

	initConsole();
	nextLine = printQuotesTableHeads(0);
	
	while(keep_running)
	{
		char key = catchKey();
		if(key == 'q' || key == 'Q')
		{
			std::cout << "�����ص��ϼ��˵�..." << key << std::endl;
			keep_running = false;
			parimary();
			return;
		}
		printQuotesTableData(nextLine);

	}
}

void Menu::trade()
{
	TRADE_START:
	system("cls");
	string stockCode;
	vector<Stock>::iterator findit;
	int stockIndex = -1;
	int nextLine;
	nextLine = printTradeStartTableHeads(0);
	cin >> stockCode;
	if(stockCode == "q" || stockCode == "Q") 
	{
		parimary();
		return;
	}

	findit = opt::stock::findStockInVector(stockCode);
	//������ڸù�Ʊ
	if(findit != stocks.end())
	{
		Entrust entrust;
		Holdshare holdshare;
		string confirmed;
		string input;
		
		entrust.username=actuser.username;
		nextLine = printTradeChosenStockTable(nextLine, *findit);
	TRADE_STOCK_ISBUY:
		cout << "��������<����1Ϊ���룬0Ϊ����, q����> : ";
		cin  >> input;
		// checkTradeInput(entrust.isbuy);
		if(input == "q" || input == "Q") goto TRADE_START;
		if(input == "1")
		{
			entrust.isbuy = true;
		}
		else if(input == "0")
		{
			entrust.isbuy = false;
		}
		else 
		{
			goto TRADE_STOCK_ISBUY;
		}
	TRADE_STOCK_PRICE:	
		cout << "��Ʊί�м�<������ֵ, q����>: ";
		cin  >> input;
		if(input == "q" || input == "Q") goto TRADE_START;
		entrust.price = atof(input.c_str());
		if(entrust.price < (0.90 * findit->nowPrice) || entrust.price > (1.10 * findit->nowPrice)) {
			cout << "���ĳ��۲����������ǵ�����10%�޼۵�ί��Ϊ��Чί��." <<endl;
			goto TRADE_STOCK_PRICE;
		}
	TRADE_STOCK_NUM:
		cout << "�����Ʊ����<������ֵ, q����>: ";
		cin  >> entrust.num;
		if (entrust.num <=0){
			goto TRADE_STOCK_NUM;
		}
	TRADE_STOCK_CFM:
		cout << "ȷ��������Ϣ<����yȷ�ϣ�q����>:"; 
		cin  >> confirmed;
		if(confirmed == "Y" || confirmed == "y")
		{   
			entrust.time=Time();
			entrust.code = findit->code;
			findit->entrust.push_back(entrust);
			sort(findit->entrust.begin(), findit->entrust.end(), opt::cmp::entrust);
			//ί�н��ױ�
			transactions[actuser.username].push_back(entrust);
			//�ֱֲ�
			bool test = opt::stock::updateHoldshare(entrust, findit->name);	
			cout<< "���׳ɹ�!" << test << endl;
			cout<< "��Ʊ����: " << entrust.code << ", �ɽ��۸�: " << entrust.price << ", �ɽ�����: " << entrust.num << endl;
			system("pause");
			parimary();	
			return;
		}
		else if(confirmed == "q" || confirmed == "Q")
		{
			goto TRADE_START;
		}
		else
		{
			goto TRADE_STOCK_CFM;
		}
	}		 
	else
	{
		cout<<"���޴˹�,����������"<<endl;
		system("pause");
		trade();
	}
}

void Menu::record()
{
	string input;
	printUserEntrustRecord(actuser, 0);
	system("pause");
	parimary();	
	return;

}

void Menu::myhold()
{
	printMyHoldShare(0);
	system("pause");
	parimary();	
	return;
}

void Menu::error()
{
	cout<< "����������������룡" <<endl;
	system("pause");
	parimary();
	return;
}

