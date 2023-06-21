#include <iostream>

using std::string;

struct DataEntry
{
    char name[32];
    int value;
    DataEntry* next_entry{ nullptr };
};

void switchEntries(DataEntry* entry1, DataEntry* entry2)
{
    string tempName;
    tempName.resize(32);
    tempName = entry1->name;
    tempName.resize(32);
    int tempValue = entry1->value;

    for (int i = 0; i < 32; i++)
    {
        entry1->name[i] = entry2->name[i];
    }
    entry1->value = entry2->value;

    for (int i = 0; i < 32; i++)
    {
        entry2->name[i] = tempName[i];
    }

    entry2->value = tempValue;
}

void compareAndSwitch(DataEntry* first, DataEntry* second)
{
    const string firstName = first->name;
    const string secondName = second->name;

    if (firstName == secondName && second->value > first->value)
    {
        switchEntries(first, second);
        return;
    }
    for (int i = 0; i < firstName.size(); i++)
    {
        if (i > secondName.size())
        {
            switchEntries(first, second);
            return;
        }

        if (firstName[i] > secondName[i])
        {
            switchEntries(first, second);
            return;
        }
        else if (firstName[i] < secondName[i])
        {
            return;
        }
    }
}

DataEntry* sortListAlphabetically(DataEntry* entries)
{
    for (DataEntry* entry = entries; entry != nullptr; entry = entry->next_entry)
    {
        for (DataEntry* entryNext = entry->next_entry; entryNext != nullptr; entryNext = entryNext->next_entry)
        {
            compareAndSwitch(entry, entryNext);
        }
    }

    return entries;
}


int main()
{
    DataEntry entries[] = {
        DataEntry{"Michael",5,&entries[1]},
        DataEntry{"Gaben",6,&entries[2]},
        DataEntry{"Elliot",3,&entries[3]},
        DataEntry{"Elliot",25,&entries[4]},
        DataEntry{"Trian",2,&entries[5]},
        DataEntry{"Abigail",15,&entries[6]},
        DataEntry{"Charlie",1,nullptr}
    };

    for (const DataEntry* entry = entries; entry != nullptr; entry = entry->next_entry)
    {
        std::cout << entry->name << " : " << entry->value << " : ";
    }

    std::cout << std::endl;

    sortListAlphabetically(entries);

    for (const DataEntry* entry = entries; entry != nullptr; entry = entry->next_entry)
    {
        std::cout << entry->name << " : " << entry->value << " : ";
    }

}
