#ifndef COMBINATION_HPP
#define COMBINATION_HPP
#include <list>
#include "Combination_Input.hpp"
#include "Combination_Output.hpp"

class Combination
{
public:
    Combination(Combination_Input input, std::list<Combination_Output> outputs, float profit_margin, float money_lost_in_worst_case);
    void add_input(Combination_Input input);
    std::list<Combination_Input> get_inputs() const;
    std::list<Combination_Output> get_outputs() const;
    float get_profit_margin() const;
    float get_money_lost_in_worst_case() const;

private:
    std::list<Combination_Input> m_combination_inputs;
    std::list<Combination_Output> m_combination_outputs;
    float m_profit_margin;
    float m_money_lost_in_worst_case;
};

#endif