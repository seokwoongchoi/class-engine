#pragma once
#include "stdafx.h"

struct Progress
{
	Progress() { Clear(); }

	void Clear()
	{
		status.clear();
		jobsDone = 0;
		jobCount = 0;
		bLoading = false;
	}
	string status;
	int jobsDone;
	int jobCount;
	bool bLoading;
};
class ProgressReport
{
public:
	static ProgressReport& Get()
	{
		static ProgressReport instance;
		return instance;
	}
	const string GetStatus(const int& progressID)
	{
		return reports[progressID].status;
	}
	const float GetPercentage(const int& progressID)
	{
		float jobsDone = static_cast<float>(reports[progressID].jobsDone);
		float jobCount = static_cast<float>(reports[progressID].jobCount);

		return jobsDone / jobCount;
	}

	const bool IsLoading(const int& progressID)
	{
		return reports[progressID].bLoading;
	}
	void SetStatus(const int& progressID, const string& status)
	{
		reports[progressID].status = status;
	}
	void SetjobsDone(const int& progressID, const int& jobsDone)
	{
		reports[progressID].jobsDone = jobsDone;
	}
	void SetjobCount(const int& progressID, const int& jobCount)
	{
		reports[progressID].jobCount = jobCount;
	}
	void SetIsLoading(const int& progressID, const bool& bLoading)
	{
		reports[progressID].bLoading = bLoading;
	}
	void IncrementJobsDone(const int& progressID)
	{
		reports[progressID].jobsDone++;
	}
	void Reset(const int& progressID) 
	{
		reports[progressID].Clear(); 
	}
private:
	ProgressReport(){}
	virtual ~ProgressReport(){}

private:
	map<int, Progress>reports;



};

