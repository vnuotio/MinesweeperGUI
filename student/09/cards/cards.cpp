#include "cards.hh"

// TODO: Implement the methods here
Cards::Cards(): top_(nullptr)
{
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
