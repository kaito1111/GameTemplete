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

	//�o�ߎ��Ԃ��擾�i�P�ʁE�b�j
	double GetElased() const
	{
		return elapsed;
	}

	//�o�ߎ��Ԃ��擾�i�P�ʁE�~���b�j
	double GetElapesedMillsecond()const 
	{
		return elapsedMill;
	}

	//�o�ߎ��Ԃ��擾�i�P�ʁE�}�C�N���b�j
	double GetElapsedMicrosecond() const 
	{
		return elapsedMicro;
	}
private:
	LONGLONG frep = 0;
	LONGLONG end = 0;
	LONGLONG begin = 0;
	double elapsed = 0.0;		//�o�ߎ��ԁi�P�ʁE�b�j
	double elapsedMill = 0.0;	//�o�ߎ��ԁi�P�ʁE�~���b�j
	double elapsedMicro = 0.0;	//�o�ߎ��ԁi�P�ʁE�}�C�N���b�j
};

