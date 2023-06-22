#include <iostream>

using std::string;

struct DataEntry
{
    char name[32];
    int value;
    DataEntry* next_entry{ nullptr };
};

DataEntry* sortListAlphabetically(DataEntry* entries)
{
    DataEntry* newEntry{ nullptr };

    for (DataEntry* entry = entries; entry != nullptr; entry = entry->next_entry)
    {
        for (DataEntry* entryNext = entry->next_entry; entryNext != nullptr; entryNext = entryNext->next_entry)
        {
            compareAndSwitch(entry, entryNext);
        }
    }

    return entries;
}

void compareAndSwitch(DataEntry* first, DataEntry* second)
{
    const string firstName = first->name;
    const string secondName = second->name;

    for (int i = 0; i < firstName.size(); i++)
    {
        if (i > secondName.size())
        {
            switchEntries(first, second);
        }

        if (firstName[i] > secondName[i])
        {
            switchEntries(first, second);
        }
        else if (firstName[i] == secondName[i])
        {
            // do nothing
        }
    }
}

void switchEntries(DataEntry* entry1, DataEntry* entry2)
{
    string tempName;
    tempName.resize(32);
    string tempName = entry1->name;
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
int main()
{
    DataEntry entries[] = {
        DataEntry{"memet",5,&entries[1]},
        DataEntry{"mustafa",6,&entries[2]},
        DataEntry{"musab",3,&entries[3]},
        DataEntry{"ahmet",2,&entries[4]},
        DataEntry{"burhan",1,&entries[5]}

    };


    for (const DataEntry* entry = entries; entry != nullptr; entry = entry->next_entry)
    {
        std::cout << entry->name << " : ";
    }

    std::cout << std::endl;

    sortListAlphabetically(entries);

    for (const DataEntry* entry = entries; entry != nullptr; entry = entry->next_entry)
    {
        std::cout << entry->name << " : ";
    }
}
