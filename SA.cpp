#include<bits/stdc++.h>
#define pb() (double)rd()/(double)rd.max()
#define pdd pair<double,double>
#define xpos first
#define ypos second

using namespace std;

mt19937 rd(time(0));

class SASystem{
public:
	SASystem(int iter,double t,double rt){
		dataInput();
		moveidx=vector<int>(CityName.size());
		Iter=iter;
		T=t;
		Rt=rt;
	}
	
	void dataInput(){
		freopen("SAinputData.txt","r",stdin);
		string dataline;
	
		while(cin>>dataline){
			stringstream ss;
			for(int a=0;a<dataline.length();a++)if(dataline[a]==',')dataline[a]=' ';
			ss<<dataline;
			string Name;
			double x,y;
			ss>>Name>>x>>y;
			CityName.push_back(Name);
			CityPos.push_back(make_pair(x,y));
		}
	}
	
	void exe(){	
		init();
		for(int a=0;a<Iter;a++){
			vector<int> iterResult=modify(moveidx);
			if(Determination(value(iterResult)))moveidx=iterResult;
			T*=Rt;
			if(bestResult.size()==0||value(moveidx)<value(bestResult)){
				bestResult=moveidx;
				PrintResult(a+1);
			}
		} 
	}
	
private:
	void init(){
		vector<int> idx(CityName.size());
		for(int a=0;a<CityName.size();a++)idx[a]=a;
		
		for(int a=0;a<moveidx.size();a++){
			int id=rd()%idx.size();
			moveidx[a]=idx[id];
			idx.erase(idx.begin()+id);
		}
		bestResult=moveidx;
		PrintResult(0);
	}
	
	vector<int> modify(vector<int> data){
		int id1=rd()%data.size(),id2=rd()%data.size();
		
		while(id1==id2)id1=rd()%data.size();
		swap(data[id1],data[id2]);
		
		return data;
	}

	double CityDis(pdd c1,pdd c2){
		return sqrt(pow(c1.xpos-c2.xpos,2)+pow(c1.ypos-c2.ypos,2));
	}

	double value(vector<int> &data){
		double dis=0;
		for(int a=0;a<data.size();a++){
			if(a<data.size()-1)dis+=CityDis(CityPos[data[a]],CityPos[data[a+1]]);
			else dis+=CityDis(CityPos[data[a]],CityPos[data[0]]);
		}
		
		return dis;
	}

	bool Determination(double v){
		double nowV=value(moveidx);
		if(v<=nowV)return true;		

		if(pb()<exp((nowV-v)/T))return true;
		
		return false;
	}

	void PrintResult(int iter){
		if(iter>0)cout<<"<In Iter："<<iter<<" have a Better Result>"<<endl;
		else cout<<"<Initial Result>"<<endl;
		for(int b=0;b<bestResult.size();b++)cout<<CityName[bestResult[b]]<<"->";
		cout<<CityName[bestResult[0]]<<endl<<"total distance："<<value(bestResult)<<endl;
		cout<<endl;
	}

	vector<string> CityName;//城市名稱 
	vector<pdd> CityPos;//城市座標 
	
	vector<int> moveidx,bestResult;//移動路徑、好執行結果  
	
	int Iter;//迭代次數
	double T,Rt;//溫度、退火係數 
};

int main(){
	SASystem sys(10000,1.0,0.99);
	sys.exe();
}
