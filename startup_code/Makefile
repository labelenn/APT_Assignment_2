.default: all

all: ppd

clean:
	rm -rf ppd *.o *.dSYM

ppd: Coin.o Node.o LinkedList.o ppd.o helper.o CashRegister.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^


# TODO - Learn what make files are
# PurchaseTests := Item_overpay
# RemoveItemTests := Remove
# ResetCoinTests := reset
# ResetStockTests := reset
# SaveExitTests := SaveExit

# testGroups := PurchaseTests RemoveItemTests ResetCoinTests ResetStockTests SaveExitTests

# Fix later
test:
	@echo "----------------------------------"
	@echo "Test: Item overpay"
	@./ppd stock.dat coins.dat <tests/PurchaseTests/Item_overpay.input > tests/PurchaseTests/Item_overpay.actual_ppd_out
	@diff -w tests/PurchaseTests/Item_overpay.output tests/PurchaseTests/Item_overpay.actual_ppd_out
	@diff -w tests/PurchaseTests/Item_overpay.expcoins coins.dat
	@echo "----------------------------------"