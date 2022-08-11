#include "Combination.hpp"

Combination::Combination(Combination_Input input, std::list<Combination_Output> outputs, float profit_margin, float money_lost_in_worst_case)
    : m_combination_outputs(outputs), m_profit_margin(profit_margin), m_money_lost_in_worst_case(money_lost_in_worst_case)
{
    m_combination_inputs = std::list<Combination_Input>();
    m_combination_inputs.push_back(input);
}

void Combination::add_input(Combination_Input input)
{
    m_combination_inputs.push_back(input);
}

std::list<Combination_Input> Combination::get_inputs() const
{
    return m_combination_inputs;
}

std::list<Combination_Output> Combination::get_outputs() const
{
    return m_combination_outputs;
}

float Combination::get_profit_margin() const
{
    return m_profit_margin;
}

float Combination::get_money_lost_in_worst_case() const
{
    return m_money_lost_in_worst_case;
}