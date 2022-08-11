# CSGO Market Analyzer

The Steam Market for Counter-Strike Global Offensive is huge, and as a normal user, its really hard to analyze the market and search the profitations of buying and selling the good items.
Because of this, I introduce an automated solution for this job, you can still work or do other stuff while the program will search.

## How it works?

CSGO system gives to users the possibility to consume 10 weapons of the same collection and the same rarity => 1 weapon of the same collection with rarity superior than the previous.

But the wear float value of the output weapon really really counts, CSGO reveals that the calculation of this value is not random, and it uses the following formula:

`(max_output - min_ouput) * median_input_value + min_output = output_value`

Now because we know the formula, it is possible for the program to search the offers that if we buy it 10 times, it will give us something more valuable.

# How to use?

The program is compiled in C++, i left a makefile for Linux distros, but you must install libraries needed for the program to actually create the program (in `build` directory)

## Libraries used

- [SQLite3](https://sqlite.org/cintro.html)
- [Boost](https://www.boost.org/)
- [nlohmann JSON](https://github.com/nlohmann/json) (for reading JSON)
- [Bass](https://www.un4seen.com/) (for audio)

## TODO in the future

- `Create an auto buy option` : this step needs to verify if the application works perfectly atleast some months before passing to actual money.

# License
[GNU General Public License v2.0](LICENSE)
