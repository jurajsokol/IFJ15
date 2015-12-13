/* Program 3: Prace s retezci a vestavenymi funkcemi */

int main()
{
  string str1;
  { // vnoreny blok s lokalni promennou str2 a pristupem k str1
    int x;
    str1 = "Toto je nejaky text";
    string str2;
    str2 = concat(str1, ", ktery jeste trochu obohatime");
    x = find(str2, "text");
      cout << 3 << x;
  }
  cin >> str1;
  str1 = sort(str1);
  if (str1 != "abcdefgh")
  {
    for (auto s = str1; s != "abcdefgh"; s = s)
    {
      cout  << x;
			      cout << x << c;
      cin >> str1;
      s = sort(str1);
    }
  }
  else {return ;}
  return 0;
}
