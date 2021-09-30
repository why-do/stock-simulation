#ifndef STOCKAPP_OUTPUT_H
#define STOCKAPP_OUTPUT_H

#include "data.h"
#include "lib/winconsole.h"
#include <algorithm>
#include <vector>

// ������ͷ
const vector<string> ENTRUST_TABLEHEAD  = {"��Ʊ����","�û�","�Ƿ�����","ί�м۸�","ί������","ί��ʱ��"};
const vector<string> QUOTES_TABLEHEAD  = {"����","����","�ּ�","�Ƿ�%","�ǵ�","���","����","������","����","�ܽ��","��ͨ��ֵ","��ӯ��","�о�ֵ"}; 
const vector<string> TRADE_ENSURE_TABLEHEAD  = {"��Ʊ����","����","ί�м�"}; 
const vector<string> TRADE_STOCK_ENTRUST_TABLEHEAD  = {"ί���û�","�Ƿ�����","ί�м۸�","ί������","ί��ʱ��"};
const vector<string> TRADE_HOLDSHARE_TABLEHEAD  = {"��Ʊ����","��Ʊ����","����","�ɱ���","���¼�","��ֵ","�ϼ�ӯ��"}; 


// ��ӡ���ݱ��ͷ
int printTableHeads(int displayLine, vector<string> tableHeads)
{    
    setPrintLine(displayLine);
    for(int i=0; i< tableHeads.size(); i++){
        printField(colorType::WHITE, tableHeads[i]);
    }
    displayLine = printFieldsFinal(displayLine);
    return displayLine;
}


//----------Quotes
int printQuotesTableHeads(int startLine)
{
    int nextLine;
    nextLine = printSplitLine(startLine);
    nextLine = printCenterLine(nextLine, "��Ʊ����");
    nextLine = printSplitLine(nextLine);
    nextLine = printTableHeads(nextLine, QUOTES_TABLEHEAD);
    return nextLine;

}

int printQuotesTableData(int startLine)
{   
    string increaseFixSign;
    float totalAmountFix;
    enum colorType majorColor;
    for(int i=0; i<stocks.size(); i++){

        if(stocks[i].increaseRate >= 0) {
            majorColor = colorType::RED;
            increaseFixSign = "+";
        }else{
            majorColor = colorType::GREEN;
            increaseFixSign = "";
        }
        totalAmountFix = stocks[i].totalAmount/10000;
        setPrintLine(startLine);
        printField(colorType::WHITE, stocks[i].name);
        printField(colorType::WHITE, stocks[i].code);
        printField(majorColor, stocks[i].nowPrice);
        printField(majorColor, increaseFixSign, stocks[i].increaseRate);
        printField(majorColor, increaseFixSign, stocks[i].increaseValue);
        printField(majorColor, stocks[i].buyPrice);
        printField(majorColor, stocks[i].sellPrice);   
        printField(colorType::BLUE, stocks[i].turnoverRate, "%");
        printField(colorType::BLUE, stocks[i].totolHand);
        printField(colorType::BLUE, totalAmountFix, "��");
        printField(colorType::BLUE, stocks[i].circMarketValue, "��");
        printField(colorType::WHITE, stocks[i].peRatio);
        printField(colorType::WHITE, stocks[i].pbRatio);
        startLine = printFieldsFinal(startLine);
    }
    startLine = printLineEnd(startLine, "<����q�˻��ϼ��˵�>");
    return startLine;
}

//--------Trade
int printTradeStartTableHeads(int startLine)
{
    int nextLine;
    nextLine = printSplitLine(startLine);
    nextLine = printCenterLine(nextLine, "֤ȯ����");
    nextLine = printSplitLine(nextLine);
    nextLine = printLine(nextLine, "ʾ����Ʊ: ");
    for(int i=0; i< stocks.size(); i++){
        setPrintLine(nextLine);
        printField(colorType::WHITE, stocks[i].name);
        printField(colorType::WHITE, stocks[i].code);
        nextLine = printFieldsFinal(nextLine);
    }
    nextLine = printSplitLine(nextLine);
    nextLine = printLine(nextLine, "������Ҫ���׵Ĺ�Ʊ����<����q����>: ");
    return nextLine;
}

//��ѡ���Ʊ��ϸ��Ϣ
int printTradeChosenStockTable(int startLine, Stock stock)
{    
    int nextLine;
    string increaseFixSign;
    float totalAmountFix;
    enum colorType majorColor;
    int entrustsize;
    nextLine = printSplitLine(startLine);
    nextLine = printLine(nextLine,"��ѡ��Ĺ�Ʊ��Ϣ: ");
    //��ӡ���ݱ�ͷ
    nextLine = printTableHeads(nextLine, TRADE_ENSURE_TABLEHEAD);
    if(stock.increaseRate >= 0) {
        majorColor = colorType::RED;
        increaseFixSign = "+";
    }else{
        majorColor = colorType::GREEN;
    }
    totalAmountFix = stock.totalAmount/10000;
    //��ӡ����
    setPrintLine(nextLine);
    printField(colorType::WHITE, stock.name);
    printField(colorType::WHITE, stock.code);
    printField(majorColor, stock.nowPrice);
    nextLine = printFieldsFinal(nextLine);
    nextLine = printSplitLine(nextLine);
    //��ӡ��Ʊί����Ϣ
    entrustsize = stock.entrust.size() > 5 ? 5 : stock.entrust.size() ;
    //"�ù�Ʊ�������ί��������£�
    //-----------------------------------------------------------
    //ί���û�  �Ƿ�����  ί�м۸�  ί������  ί��ʱ��
    //-----------------------------------------------------------
    if(entrustsize==0) 
    {
        nextLine = printLineEnd(nextLine, "�ù�ƱĿǰ��δ��ί�м�¼��");    
    }
    else{
        nextLine = printLine(nextLine, "�ù�Ʊ�������ί��������£�");
        nextLine = printTableHeads(nextLine, TRADE_STOCK_ENTRUST_TABLEHEAD);
        for(int j=0; j<entrustsize; j++) 
        {  
            setPrintLine(nextLine);
            printField(colorType::WHITE, stock.entrust[j].username);
            printField(colorType::WHITE, stock.entrust[j].code);
            printField(colorType::WHITE, stock.entrust[j].price);
            printField(colorType::WHITE, stock.entrust[j].num);
            printField(colorType::WHITE, stock.entrust[j].time.parse());
            nextLine = printFieldsFinal(nextLine);
        }
    }
    nextLine = printSplitLine(nextLine);
    setPrintLine(nextLine);
    return nextLine;
}

// ��ӡ�ù�Ʊ��ί����Ϣ
int printStockEntrustRecord(int startLine, Stock stock)
{   
    int nextLine;
    // ��Ʊ���� �û�  �Ƿ�����  ί�м۸�  ί������  ί��ʱ��      
    nextLine = printSplitLine(nextLine);
    nextLine = printTableHeads(nextLine, ENTRUST_TABLEHEAD);
    nextLine = printSplitLine(nextLine);
    nextLine = printStockEntrustRecord(nextLine, stock);
    
    for(int i=0; i< stock.entrust.size(); i++){
        setPrintLine(nextLine);
        printField(colorType::WHITE, stock.entrust[i].username);
        printField(colorType::WHITE, stock.entrust[i].price);
        printField(colorType::WHITE, stock.entrust[i].isbuy);
        printField(colorType::WHITE, stock.entrust[i].num);
        printField(colorType::WHITE, stock.entrust[i].time.parse());
        nextLine = printFieldsFinal(nextLine);
        nextLine ++;
    }
    return nextLine;
}

// �˵�������ӡ�û���ί����Ϣ
int printUserEntrustRecord(User user, int startLine)
{   
    int nextLine;
    system("cls");
    nextLine = printSplitLine(startLine);
    nextLine = printCenterLine(nextLine, "�ҵ�ί�н��׼�¼");
    // ��Ʊ���� �û�  �Ƿ�����  ί�м۸�  ί������  ί��ʱ��      
    nextLine = printSplitLine(nextLine);
    nextLine = printTableHeads(nextLine, ENTRUST_TABLEHEAD);
    nextLine = printSplitLine(nextLine);
    for(int i=0; i<transactions[user.username].size(); i++){
        setPrintLine(nextLine);
        printField(colorType::WHITE, transactions[user.username][i].code);
        printField(colorType::WHITE, transactions[user.username][i].username);
        printField(colorType::WHITE, transactions[user.username][i].isbuy);
        printField(colorType::WHITE, transactions[user.username][i].price);
        printField(colorType::WHITE, transactions[user.username][i].num);
        printField(colorType::WHITE, transactions[user.username][i].time.parse());
        nextLine = printFieldsFinal(nextLine);
        
    }
    setPrintLine(nextLine);
    return nextLine;
}


//-------holdShare

int printMyHoldShare(int startLine)
{
    int nextLine;
    vector<Stock>::iterator it;
    Holdshare *rec;
    system("cls");
    nextLine = printSplitLine(startLine);
    //test
    printLineEnd(nextLine, holdshares[actuser.username].size());
    nextLine = printCenterLine(nextLine, "�ҵĳֲ�");
    nextLine = printSplitLine(nextLine);
    if(holdshares[actuser.username].size() != 0){
        nextLine = printTableHeads(nextLine, TRADE_HOLDSHARE_TABLEHEAD);
        for(int i=0; i<holdshares[actuser.username].size(); i++){
            if(holdshares[actuser.username][i].num != 0){
                rec = &holdshares[actuser.username][i];
                //"��Ʊ����","��Ʊ����","����","�ɱ���","���¼�","��ֵ","�ϼ�ӯ��"        
                it = find(stocks.begin(), stocks.end(), rec->code);
                if( it != stocks.end())
                {
                    printField(colorType::WHITE, rec->code);
                    printField(colorType::WHITE, it->name);
                    printField(colorType::WHITE, rec->num);
                    printField(colorType::WHITE, rec->price);
                    printField(colorType::WHITE, it->nowPrice);
                    printField(colorType::WHITE, it->nowPrice * rec->num);
                    printField(colorType::WHITE, (it->nowPrice - rec->price) * rec->num);
                    nextLine = printFieldsFinal(nextLine);
                }
                
            }
        }
    }
    else
    {
        nextLine = printLineEnd(nextLine,"��Ŀǰû�гֲּ�¼��"); 
    }
    return nextLine;
}



int printWelcomeTable(int startLine)
{   
    int nextLine;
    Time time;
    initConsole();
    system("title ��Ʊ���齻��ģ��ϵͳ");
    nextLine = printSplitLine(startLine);
    nextLine = printCenterLine(nextLine, "��ӭʹ�ù�Ʊ���齻��ģ��ϵͳ!"); 
    nextLine = printCenterLine(nextLine, "��ǰʱ��: " + time.parse());
    nextLine = printCenterLine(nextLine, "��ǰ��¼�û�: " + actuser.username);
    nextLine = printSplitLine(nextLine);
    setPrintLine(nextLine);
    return nextLine;
}

int printParimaryMenu(int startLine)
{
    char sel;
    int nextLine = 0;
    Time t;
    initConsole();
    nextLine = printSplitLine(startLine);
    nextLine = printCenterLine(nextLine, "����ѡ��");
    nextLine = printSplitLine(nextLine);
    nextLine = printLine(nextLine, "1.�����ѯ");
    nextLine = printLine(nextLine, "2.��Ʊ����");
    nextLine = printLine(nextLine, "3.�ҵ�ί�м�¼");
    nextLine = printLine(nextLine, "4.�ҵĳֲ�");
    nextLine = printLine(nextLine, "5.�˳�ϵͳ");
    nextLine = printSplitLine(nextLine);
    nextLine = printLine(nextLine, "������: ");
    return nextLine;

}
#endif