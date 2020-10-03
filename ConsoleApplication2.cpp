#include <iostream> 
using namespace std;

class DateTime
{
	int Entry;

	static int getNoOfDays(const int& month, const int& year)
	{
		switch (month)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;

		case 4:
		case 6:
		case 9:
		case 11:
			return 30;

		case 2:
			if (year % 4 || year == 2100)
				return 28;
			else return 29;
		}
	}

	static bool IsValidDate(const int& year, const int& month, const int& day)
	{
		if (year < 1980 || month < 1 || day < 1)
			return false;

		if (year > 2107 || month > 12)
			return false;

		if (day > getNoOfDays(month, year))
			return false;

		return true;
	}

	static bool IsValidTime(const int& hour, const int& minute, const int& second)
	{
		if (hour < 0 || minute < 0 || second < 0)
			return false;

		if (hour > 23 || minute > 59 || second > 59)
			return false;

		return true;
	}

	static int MapDate(const int& year, const int& month, const int& day)
	{
		int mappedDate = year - 1980;
		mappedDate = mappedDate << 4 | month;
		mappedDate = mappedDate << 5 | day;

		return mappedDate;
	}

	static int MapTime(const int& hour, const int& minute, const int& second)
	{
		int mappedTime = hour;
		mappedTime = mappedTime << 6 | minute;
		mappedTime = mappedTime << 5 | (second / 2);

		return mappedTime;
	}
	// Define more methods for help here
	// ....
public:
	DateTime(const int& Year = 2017, const int& Month = 1, const int& Day = 1,
		const int& Hour = 0, const int& Minute = 0, const int& Second = 0)
	{
		if (!IsValidDate(Year, Month, Day) || !IsValidTime(Hour, Minute, Second))
			throw "Invaid Timing!!";

		Entry = (MapDate(Year, Month, Day) << 16) | MapTime(Hour, Minute, Second);
	}

	void SetYear(const int& newYear)
	{
		Entry = (Entry << 7) >> 7 | ((newYear - 1980) << 25);
	}
	void SetMonth(const int& newMonth)
	{
		int temp = Entry >> 25;
		temp = (temp << 25) | (newMonth << 21);
		Entry = (Entry << 11) >> 11 | temp;
	}
	void SetDay(const int& newDay)
	{
		int temp = Entry >> 21;
		temp = (temp << 21) | (newDay << 16);

		Entry = (Entry << 16) >> 16 | temp;
	}
	void SetHour(const int& newHour)
	{
		int temp = Entry >> 16;
		temp = (temp << 16) | (newHour << 11);
		Entry = (Entry << 21) >> 21 | temp;
	}
	void SetMinute(const int& newMinute)
	{
		int temp = Entry >> 11;
		temp = (temp << 11) | (newMinute << 5);
		Entry = (Entry << 27) >> 27 | temp;
	}
	void SetSecond(const int& newSecond)
	{
		Entry = (Entry >> 5) | (newSecond / 2);
	}
	void SetDate(const int& newYear, const int& newMonth, const int& newDay)
	{
		SetYear(newYear);
		SetMonth(newMonth);
		SetDay(newDay);
	}
	void SetTime(const int& newHour, const int& newMinute, const int& newSecond)
	{
		SetHour(newHour);
		SetMinute(newMinute);
		SetSecond(newSecond);
	}

	int GetYear()
	{
		return (Entry >> 25) + 1980;
	}
	int GetMonth()
	{
		int month = (Entry << 7);
		return (Entry << 7) >> 28;
	}
	int GetDay()
	{
		return (Entry << 11) >> 27;
	}
	int GetHour()
	{
		return (Entry << 16) >> 27;
	}
	int GetMinute()
	{
		return (Entry << 21) >> 26;
	}
	int GetSecond()
	{
		return ((Entry << 27) >> 27) * 2;
	}
	void GetDate(int& Year, int& Month, int& Day)
	{
		Year = GetYear();
		Month = GetMonth();
		Day = GetDay();
	}
	void GetTime(int& Hour, int& Minute, int& Second)
	{
		Hour = GetHour();
		Minute = GetMinute();
		Second = GetSecond();
	}

	void test() { cout << Entry; }
};

int main()
{
	DateTime d(1987, 12, 31, 12, 54, 46);
	int date[3], t[3];

	d.GetDate(date[0], date[1], date[2]);
	d.GetTime(t[0], t[1], t[2]);

	//cout << date[0] << "/" << date[1] << "/" << date[2] << " " << t[0] << " " << t[1] << " " << t[2]<<endl;
	d.test();
}