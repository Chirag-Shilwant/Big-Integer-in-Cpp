#include <bits/stdc++.h>
using ll = long long int;
using ld = long double;
#define MAX 19
ll gcdAns;
using namespace std;

class Operations{

    public:

    string factorial(string num)
    {

        if(num == "0" or num == "1" ) return "1";

        if(num == "2") return num;

        string ans = "1";

        for(ll i=2; i <= stoll(num); i++)
        {
            ans  = multiply(ans, to_string(i));
        }
        return ans;
    }

    string fastExpo(string a, ll b)
    {
        if(b == 0) return "1";

        if(b == 1) return a;

        string ans = "1";

        while(b)
        {
            if(b % 2)
            ans = multiply(ans, a);

            b /= 2;
            a = multiply(a, a);
        }

        return ans;
    }

    // GCD of (ll, ll)
    ll gcD(ll num1, ll num2)
    {
       if(num2 == 0)
         return num1;

       return gcD(num2, num1 % num2);    
    }

    // GCD of (string, ll)
    ll gcD(string num1, ll num2)
    {
      if(num2 == 0)
         return stoll(num1);

       return gcD(num2, modulo(num1, num2));       
    }

   // Repetitve Subtraction
   string gcD1(string num1, string num2)
    {
        if(num1 == "0") return num2;
        if(num2 == "0") return num1;
   
      bool ansMila = false;

      while(num2[0] > '0')
      {

        if(great(num1, num2))
        { 
            if((num1.size() < MAX) and (num2.size() < MAX) )
                {
                    Operations g; 
                    gcdAns = g.gcD(stoll(num1), stoll(num2));
                    ansMila = true;
                    break;
                }
                else if(num2.size() < MAX)
                {
                     Operations g; 
                    gcdAns = g.gcD(num1, stoll(num2));
                    ansMila = true;
                    break;
                }
                else if(num1.size() < MAX)
                {
                     Operations g; 
                   gcdAns = g.gcD(num2, stoll(num1));
                   ansMila = true;
                    break;
                }
                else 
                  num1 = subtract(num1, num2);
                
        }
        else
        {
              if((num1.size() < MAX) and (num2.size() < MAX) )
                {
                    
                    Operations g; 
                    gcdAns = g.gcD(stoll(num2), stoll(num1));
                    ansMila = true;
                    break;
                }
                else if(num1.size() < MAX)
                {
                     Operations g; 
                     gcdAns = g.gcD(num2, stoll(num1));
                     ansMila = true;
                     break;
                }
                else if(num2.size() < MAX)
                {
                     Operations g; 
                     gcdAns = g.gcD(num1, stoll(num2));
                     ansMila = true;
                     break;
                }
               else    
                num2 = subtract(num2, num1);
              
        }
    }

       if(!ansMila)
          return num1;

         return "-1";    
    }

    // Fast GCD
    string gcD(string a, string b)
    {
        if(b == "0") return a;

         if(a == "0") return b;    
        if(a == b) return a;

        string temp;
        bool milgaya = true;
        while(b != "0")
        {
            temp = b;
            b = modhelp(a, b);
            a = temp;
            if(a == b) return a;

             if((a.size() < MAX) and (b.size() < MAX) )
             {
                gcdAns = gcD(stoll(b), stoll(a));
                milgaya = false;
                break;
             }
            else if(a.size() < MAX)
            {
                gcdAns = gcD(b, stoll(a));
                milgaya = false;
                break;
            }
            else if(b.size() < MAX)
            {
                gcdAns = gcD(a, stoll(b));
                milgaya = false;
                break;   
            }
       }

        if(milgaya) return a;

        return "-1";

    }

    string subtract(string a, string b)
    {
        if(a != "0" and b == "0") return a;
        
        if(a == "0" and b != "0") return "-" + b;
        
        bool minus = false;
        if(great(b,a))
        {
            swap(a, b);
            minus =true;
        }

        ll sizea = a.size(), sizeb = b.size();

        ll str[1000000] = {0};

        ll carry = 0, pos = sizea-1;

        ll diff = a.size() - b.size();

        ll count=0;

        for(ll index = sizeb-1; index >= 0; index--)
        {
            ll result = (a[index + diff] -'0') - (b[index] -'0') - carry;
            
            if(result < 0)
            {
                str[pos] = result + 10;
                carry = 1;
            }
            else
            {
                str[pos] = result;
                carry = 0;
            }
            pos--;
            count++;
       
        }
        


        for(ll i = diff -1; i>=0; i--)
        {
            
            if((carry == 1) and (a[i] == '0'))
            {
                str[pos] = 9;
                pos--;
                count++;

                continue;
            }
            ll result = (a[i] - '0') - carry;
           
            str[pos] = result;
            
            pos--;
            carry = 0;
            count++;
            
        }
       
        string finalAns;
        bool milgaya = true;
        for(ll i=0; i<count; i++)
        {
            if(str[i] == 0 and milgaya) continue;

            else
            {    
                finalAns += to_string(str[i]);
                milgaya = false;
            }
        }
        if(minus) 
        {
            string finalAns1 = "-";
            finalAns1 += finalAns;
            return finalAns1;
        }

    return finalAns;
    }
 
 
string modhelp(string a, string b)
    {
        ll low = 0, high = LLONG_MAX;
        
        while(low < high)
        {
            ll mid = low + (high - low)/2;
            string mid_string = to_string(mid);
           
            string mid_m = multiply(b, mid_string);
           
            string sub_m = subtract(a,mid_m);
            
            bool check = great1(sub_m, b);
            
            if(check)
            {
                low = mid + 1;
           
            }

            else
            { 
                high = mid;
            }
        }
        string res = multiply(b, to_string(low));
        
        string aa = subtract(a, res);

        return aa;
    }
    
    string multiply(string num1, string num2)
    {
        ll len1 = num1.size(), len2 = num2.size();

        ll arr[len1+len2] = {0};

        for(ll i=len1-1; i>=0 ; i--)
        {
            for(ll j = len2-1; j>=0; j--)
            {
                ll product = (num1[i]-'0') * (num2[j]-'0');
                ll sum  = arr[i+j+1] + product;
                arr[i+j+1] = sum % 10;
                arr[i+j] += sum / 10; 
            }
        }

        string ans;
        
        for(ll i=0;i<len1+len2;i++)
        {
            if(ans.size() != 0) ans += to_string(arr[i]);
            else if(arr[i] != 0) ans += to_string(arr[i]);    
        }
        
        if(ans.size() == 0) return "0";

        return ans;
    }
    
    ll modulo(string num, ll mod)
    {
        ll ans = 0;
        for(char c : num)
        {
            ans = ans * 10 + (c - '0');
            ans = ans % mod;
        }
        return ans;
    }

    bool great(string a, string b)
    {
        int len1 = a.size(), len2 = b.size(); 
    
        if (len1 > len2) 
            return true; 

        else if (len2 > len1) 
            return false; 
    
        for (int i=0; i<len1; i++) 
        { 
            if (a[i] > b[i]) 
                return true; 

            else if (a[i] < b[i]) 
                return false; 
        } 
        return false; 
    }
    bool great1(string a, string b)
    {
        int len1 = a.size(), len2 = b.size(); 
        if(a[0] == '-') return false;
        
        if (len1 > len2) 
            return true; 

        else if (len2 > len1) 
            return false; 
    
        for (int i=0; i<len1; i++) 
        { 
            if (a[i] > b[i]) 
                return true; 

            else if (a[i] < b[i]) 
                return false; 
        } 
        return false; 
    }

};



int main()
{
    string num1, num2, choice;
     
    ll Q, n, b;
    Operations g1;
    cin >> Q;
    while(Q--)
    {
        cin >> n;
        switch(n)
        {

            case 1 : //cout << "Enter two numbers for Fast Exponent\n";
                     cin >> num1 >> b;

                     if(num1[0] == '-')
                     {
                         num1 = num1.substr(1,num1.size()-1);
                         string ans = g1.fastExpo(num1, b);
                         
                         if(b&1)
                             cout << "-" << ans << endl;
                         
                         else
                             cout << ans << endl;
                     } 

                     else
                     {
                         string ans = g1.fastExpo(num1, b);
                         cout << ans << endl;
                     }

                     break;            

            case 2 :   // cout << "Enter 2 BigInt Numbers \n";
                        cin >> num1 >> num2;
                        gcdAns = 0;
                        
                        
                        if(num1.size() < 18 and num2.size() < 18)
                        {
                            cout << g1.gcD(stoll(num1), stoll(num2)) << endl;
                        }
                        

                       else if(num1.size() < 18)
                        {
                            cout << g1.gcD( num2, stoll(num1)) << endl;
                        }
                        
                        else if(num2.size() < 18)
                        {
                            cout << g1.gcD( num1, stoll(num2)) << endl;  
                        }

                        else if((llabs((ll)num1.size() - (ll)num2.size()) <= 5))
                        {
                            
                            string ans = g1.gcD1(num1, num2);
                             if(ans == "-1") 
                                cout << gcdAns << endl; 
                            else
                                cout << ans << endl;
                        }

                        else
                         {
                            if(num2.size() > num1.size())
                                swap(num2, num1);
                                                     
                             string ans = g1.gcD(num1, num2); 
                             
                             if(ans != "-1")
                                 cout << ans << endl; 
                             else 
                                cout << gcdAns << endl;    
                        }

                        break;   
                           
            case 3 : //cout << "Enter a number to calculate factorial\n";
                     cin >> num1;
                     cout << g1.factorial(num1);
                     cout << endl;
                     break;                 
        }

    }
   
   
        return 0;
}
