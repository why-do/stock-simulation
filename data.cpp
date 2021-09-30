
#include "data.h"
#include "lib/request.h"

vector<Stock> stocks;
User actuser;//ȫ�ֱ��� ��ʾ��ǰ��¼���û�
vector<User> users; //�û����� 
map<string, vector<Entrust>> transactions;// ����
map<string, vector<Holdshare>> holdshares;// �ֲ�
vector<string> urls = 
        {
            "http://qt.gtimg.cn/q=sh600519",
            "http://qt.gtimg.cn/q=sz002594",
            "http://qt.gtimg.cn/q=sz000725",
            "http://qt.gtimg.cn/q=sh601857",
            "http://qt.gtimg.cn/q=sh601328",
            "http://qt.gtimg.cn/q=sz002174",
            "http://qt.gtimg.cn/q=sz000156",
            "http://qt.gtimg.cn/q=sz000997",
            "http://qt.gtimg.cn/q=sh600812",
            "http://qt.gtimg.cn/q=sz300459",
            "http://qt.gtimg.cn/q=sh600056",
            "http://qt.gtimg.cn/q=sz300009",
            "http://qt.gtimg.cn/q=sh603716",
            "http://qt.gtimg.cn/q=sh600362",
            "http://qt.gtimg.cn/q=sh601069",
            "http://qt.gtimg.cn/q=sh600007",
            "http://qt.gtimg.cn/q=sz002895",
            "http://qt.gtimg.cn/q=sz002119",
            "http://qt.gtimg.cn/q=sz002726",
            "http://qt.gtimg.cn/q=sh600415",
            "http://qt.gtimg.cn/q=sh601766",
            "http://qt.gtimg.cn/q=sz300077",
            "http://qt.gtimg.cn/q=sh688027",
            "http://qt.gtimg.cn/q=sz002284",
            "http://qt.gtimg.cn/q=sh605499",
            "http://qt.gtimg.cn/q=sh605337",
            "http://qt.gtimg.cn/q=sz002577",
            "http://qt.gtimg.cn/q=sh600570",
            "http://qt.gtimg.cn/q=sz002152",
            "http://qt.gtimg.cn/q=sh601360"
        };


// ����������Ҫ�޸��첽
vector<string> opt::stock::requestData(string strurl, string splitstr){
    string::size_type pos;
    vector<string> result;
    char charurl[strurl.length() + 1];
    strcpy(charurl, strurl.c_str());
    char *resData = sendRequest(charurl);
    string str = resData;
    // cout << endl << str << endl;
    delete resData,charurl;
    // return splitWithComm(str, "~");
    str+=splitstr;
    int size=str.size();

    for(int i=0; i<size; i++)
    {
        pos=str.find(splitstr, i);
        if(pos<size)
        {
            string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+splitstr.size()-1;
        }
    }
    return result;
     
}

void opt::stock::getStocksData()
{
    Stock tmp;
    int urlsLen = urls.size();
    if(stocks.size() < urlsLen)
    {
        for(int i=0; i<urlsLen; i++){
            tmp.setStockData(requestData(urls[i],"~"));
            stocks.push_back(tmp);
        }
    }
    else
    {
        for(int j=0; j<urlsLen; j++){
            tmp.setStockData(requestData(urls[j],"~"));
            stocks.at(j) = tmp;
        }
    }
    Sleep(500);
}


int opt::stock::updateHoldshare(Entrust entrust, string stockName){
    int retstatu = -1;
	bool isfind = false;
	Holdshare *rec;
	// ���ڼ�¼

    for(int i=0; i<holdshares[actuser.username].size(); i++){
        cout << "enter 2" <<endl;
        if(holdshares[entrust.username][i].code == entrust.code){
            rec = &holdshares[entrust.username][i];
            rec->name = stockName;
            if(entrust.isbuy){
                
                rec->num += entrust.num;
                rec->price = (rec->price * rec->num) + (entrust.price * entrust.num) / (rec->num + entrust.num);
            }
            else
            { //����

                if(rec->num - entrust.num) 
                {
                    retstatu = -2;
                }
                else
                {
                    rec->num = rec->num - entrust.num;
                }
                
            }
            isfind = true;
        }
    }
    if(!isfind)
    {  // �����ڼ�¼
		Holdshare hs;
		hs.name = stockName;
		hs.code = entrust.code;
		hs.num = entrust.num;
		hs.price = entrust.price;
		holdshares[actuser.username].push_back(hs);
        retstatu = 1;
    }

    return retstatu;
}


vector<Holdshare>::iterator opt::stock::findHoldshareInVector(string code)
{
    vector<Holdshare>::iterator it;
    return find(holdshares[actuser.username].begin(), holdshares[actuser.username].end(), code);
}

vector<Stock>::iterator opt::stock::findStockInVector(string code)
{
    vector<Stock>::iterator it;
    return find(stocks.begin(), stocks.end(), code);
}


bool opt::cmp::entrust(Entrust a,Entrust b)
{
    if(a.price!=b.price) return a.price>b.price;
    else return time(a.time,b.time);
}

bool opt::cmp::time(Time a,Time b)
{
	int r=0;
	r+=1*((a.s<b.s)-(a.s>b.s));
	r+=2*((a.m<b.m)-(a.m>b.m));
	r+=4*((a.h<b.h)-(a.h>b.h));
	r+=8*((a.D<b.D)-(a.D>b.D));
	r+=16*((a.M<b.M)-(a.M>b.M));
	r+=32*((a.Y<b.Y)-(a.Y>b.Y));
	return r>0;	
}




