#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  cout << fixed << setprecision(2); // set precision in output
  int years;
  double base_income, g_income;
  double living_cost;
  double invest_bal = 0.0, invest_target, g_invest;
  double cash, networth;

  // Input
  /* For simplicity, we assume all inputs are positive */
  cout << "Years: ";
  cin >> years;
  cout << "Base income: ";
  cin >> base_income;
  cout << "Income growth rate: ";
  cin >> g_income;
  cout << "Annual living cost: ";
  cin >> living_cost;
  cout << "Investment target per year: ";
  cin >> invest_target;
  cout << "Investment growth rate: ";
  cin >> g_invest;
  cout << "Starting cash: ";
  cin >> cash;

  /* Financial simulation
   * TODO: Your code begins here (DO NOT MODIFY ANYTHING ELSE)
   * Loop for each year
   *   1) Apply investment/salary growth (NO GROWTH IN THE 1st YEAR)
   *   2) Receive salary and Pay living expense
   *   3) Invest
   *   4) Calculate net worth
   */

  for (int y = 1; y<=years; y++) {
    // 1) Apply growth rates ***after the first year***
    base_income = (y == 1) ? base_income:base_income*(g_income+1);
    // cout << "Base income is "<<base_income<<endl;
    invest_bal *= (1+g_invest);

    // 2) Receive salary and Pay living expense
    cash += (base_income - living_cost);
    // cout << "Current Cash is " << cash << endl;
    // 3) Investment contribution
    if (cash >= invest_target){
      cash -= invest_target;
      invest_bal += invest_target;
    }
    else if(cash >= 0){
      invest_bal += cash;
      cash = 0;
    }

    // 4) Calculate net worth

    networth = cash+invest_bal;
    /* Your code ends here */
    // Output
    cout << "Year: " << y << " Net worth: " << networth << " Cash: " << cash
         << " Investment: " << invest_bal << endl;
  }
  return 0;
}
