#pragma once
class Stopwatch
{
public:
	Stopwatch() {};
	~Stopwatch() {};

	void Start() {
		::QueryPerformanceCounter((LARGE_INTEGER*)&begin);
	}

	void Stop() {
		::QueryPerformanceFrequency((LARGE_INTEGER*)&frep);
		::QueryPerformanceCounter((LARGE_INTEGER*)&end);
		elapsed = double(end - begin) / frep;
		elapsedMill = elapsed * 1000.0f;
		elapsedMicro = elapsedMill * 1000.0f;
	}

	//経過時間を取得（単位・秒）
	double GetElased() const
	{
		return elapsed;
	}

	//経過時間を取得（単位・ミリ秒）
	double GetElapesedMillsecond()const 
	{
		return elapsedMill;
	}

	//経過時間を取得（単位・マイクロ秒）
	double GetElapsedMicrosecond() const 
	{
		return elapsedMicro;
	}
private:
	LONGLONG frep = 0;
	LONGLONG end = 0;
	LONGLONG begin = 0;
	double elapsed = 0.0;		//経過時間（単位・秒）
	double elapsedMill = 0.0;	//経過時間（単位・ミリ秒）
	double elapsedMicro = 0.0;	//経過時間（単位・マイクロ秒）
};

