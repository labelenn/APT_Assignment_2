Information for compiling and running the program.

Compile command:
g++ -Wall -Werror -std=c++14 -O -o ppd ppd.cpp Node.cpp LinkedList.cpp Coin.cpp CashRegister.cpp Helper.cpp

Execute command:
./ppd stock.dat coins.dat



Information for compiling and running the test cases.

Run a test:
./ppd stock.dat coins.dat <tests/<subFolder>/<test>.input > tests/<subFolder>/<test>.actual_ppd_out
eg:
    - ./ppd stock.dat coins.dat <tests/PurchaseTests/Item_overpay.input > tests/PurchaseTests/Item_overpay.actual_ppd_out
    - This will run test for Item_overpay


