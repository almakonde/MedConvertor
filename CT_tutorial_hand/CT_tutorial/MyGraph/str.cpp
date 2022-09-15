#include "str.h"


namespace str
{

	std::string replace(std::string target, std::string that, std::string with) 
	{
		while(1)
		{
			std::string::size_type where1 = target.find(that);
			if(where1 != std::string::npos) 
			{
				target.replace(target.begin() + where1,	target.begin() + where1 + that.size(),	with.begin(), with.end());
			}else break;
		}

		return target;
	}

	std::string ReplaceInString(std::string s,StringPairs& repl)
	{
		if(repl.size())
		{
			for(int i=0;i<repl.size();i++)
			{
				s = replace(s, repl[i].first, repl[i].second);
			}
		}else
			return s;
		return s;

	}
	void ReplaceInFile(std::string fn,std::string nfn,StringPairs& repl)
	{
		char buf[1000];
		std::ifstream fs(fn.c_str(),std::ios::in | std::ios::binary);
		std::ofstream fs1(nfn.c_str(),std::ios::out | std::ios::binary);

		
		while(!fs.eof())
		{
			
			fs.getline(buf,1000);
			std::string ss(buf);

			std::string res = ReplaceInString(ss,repl);
			if(res.size()>1)
			{
				fs1.write(res.c_str(),res.size()-1);
				fs1 << std::endl;
			}
			
			

		}

		fs.close();
		fs1.close();
	}

	void AddPair(StringPairs& arr, std::string a, std::string b)
	{
		arr.push_back(std::pair<std::string,std::string>(a,b));
	}

	std::vector<std::string> split(const std::string& source, std::string delim) 
	{

		std::vector<std::string> result;

		int cur1=0,cur2;

		while(1)
		{
			cur1 = source.find_first_not_of(delim, cur1);
			if(cur1==-1)break;
			cur2 = source.find_first_of(delim, cur1);
			if(cur2==-1)cur2=source.length();

			result.push_back(source.substr(cur1,cur2-cur1));
			cur1=cur2+1;
		}

		return result;
	}

	float ToFloat(std::string s)
	{
		return (float)atof(s.c_str());
	}
	int ToInt(std::string s)
	{
		return atoi(s.c_str());
	}

	std::string ToString(int val)
	{
		char buf[100];
		_itoa(val,buf,10);
		return std::string(buf);
	}
	std::string ToString(float val)
	{
		char buf[100];
		sprintf_s(buf,100,"%f",val);
		return std::string(buf);
	}
	std::string ToString(vec3 val)
	{
		char buf[200];
		sprintf_s(buf,200,"%f %f %f",val.x,val.y,val.z);
		return std::string(buf);
	}

};