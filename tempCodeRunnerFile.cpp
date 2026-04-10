#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;
int main()
{
	double a, b, c, d;
	int e, g = 0;
	string s, f;
	f.clear();
	char x;
	getline(cin, s);
	for (int i = 0; i < s.length(); ++i)
		if ((s[i] <= 'z' && s[i] >= 'a') || (s[i] <= 'Z' && s[i] >= 'A'))
		{
			x = s[i];
			e = i;
			break;
		}
	if (e == 0)
		a = 1;
	else if (e == 1 && s[0] == '-')
		a = -1;
	else
	{
		for (int i = 0; i < e; f += s[i++])
			;
		a = stod(f);
		f.clear();
	}
	for (int i = e + 4; i < s.length(); ++i)
		if (s[i] == x)
		{
			g = i;
			break;
		}
	if (g == 0)
	{
		b = 0;
		for (int i = e; i < s.length(); ++i)
			if (s[i] == '=')
			{
				g = i;
				break;
			}
		if (e + 3 == g)
			c = 0;
		else
		{
			for (int i = e + 3; i < g; f += s[i++])
				;
			c = stod(f);
		}
	}
	else
	{
		if (g == e + 4)
		{
			if (s[g - 1] == '+')
				b = 1;
			else
				b = -1;
		}
		else
		{
			for (int i = e + 3; i < g; f += s[i++])
				;
			b = stod(f);
		}
		for (int i = g; i < s.length(); ++i)
			if (s[i] == '=')
			{
				e = i;
				break;
			}
		if (g + 1 == e)
			c = 0;
		else
		{
			f.clear();
			for (int i = g + 1; i < e; f += s[i++])
				;
			c = stod(f);
		}
	}
	d = b * b - 4 * a * c;
	if (d < 0)
		cout << '?';
	else if (c == 0)
	{
		if (b == 0)
			cout << x << "_1=" << x << "_2=" << "0.0000";
		else if (a * b > 0)
			cout << x << "_1=" << -b / a << ' ' << x << "_2=" << "0.0000";
		else
			cout << x << "_1=" << "0.0000" << ' ' << x << "_2=" << -b / a;
		return 0;
	}
	else if (d == 0)
		cout << x << "_1=" << x << "_2=" << fixed << setprecision(4) << -b / 2 / a;
	else if (a > 0)
		cout << x << "_1=" << fixed << setprecision(4) << (-sqrt(d) - b) / 2 / a << ' ' << x << "_2=" << fixed << setprecision(4) << (sqrt(d) - b) / 2 / a;
	else
		cout << x << "_1=" << fixed << setprecision(4) << (sqrt(d) - b) / 2 / a << ' ' << x << "_2=" << fixed << setprecision(4) << (-sqrt(d) - b) / 2 / a;
}