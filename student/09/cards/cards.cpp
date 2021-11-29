#include "cards.hh"

// TODO: Implement the methods here
Cards::Cards(): top_(nullptr)
{
}

Cards::~Cards()
{
    while (top_ != nullptr)
    {
        Card_data* remov = top_;
        top_ = top_->next;

        delete remov;
    }
}

Card_data* Cards::get_topmost()
{
    return top_;
}

void Cards::add(int id)
{
    Card_data* new_card = new Card_data{id, nullptr};
    if (top_ == nullptr)
    {
        top_ = new_card;
    }
    else
    {
        new_card->next = top_;
        top_ = new_card;
    }
}

bool Cards::remove(int &id)
{
    if (top_ == nullptr)
    {
        return false;
    }
    Card_data* remov = top_;
    id = remov->data;

    top_ = remov->next;
    delete remov;

    return true;
}

void Cards::print_from_top_to_bottom(std::ostream& s)
{
    int running_number = 1;
    Card_data* current = top_;
    while (current != nullptr)
    {
        s << running_number << ". " << current->data << "\n";
        current = current->next;
        running_number++;
    }
}

int Cards::recursive_print(Card_data *top, std::ostream &s)
{
    int running_number = 1;
    if (top->next != nullptr)
    {
        recursive_print(top->next, s);
    }
    s << running_number << ". " << top->data << "\n";
    running_number++;
    return running_number;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    if (top_ != nullptr)
    {
        recursive_print(top_, s);
    }
}

bool Cards::bottom_to_top()
{
    if (top_ == nullptr)
    {
        return false;
    }
    else if (top_->next == nullptr)
    {
        return true;
    }

    Card_data* bottas = top_;
    Card_data* rairai = bottas;
    while (bottas->next != nullptr)
    {
        rairai = bottas;
        bottas = bottas->next;
    }
    rairai->next = nullptr;
    bottas->next = top_;
    top_ = bottas;

    return true;
}

bool Cards::top_to_bottom()
{
    if (top_ == nullptr)
    {
        return false;
    }
    else if (top_->next == nullptr)
    {
        return true;
    }

    Card_data* og_top = top_;
    Card_data* jebe = top_;
    while (jebe->next != nullptr)
    {
        jebe = jebe->next;
    }
    jebe->next = og_top;
    top_ = og_top->next;
    og_top->next = nullptr;
    return true;
}
