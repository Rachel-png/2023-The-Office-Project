#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Object {
public:
  string name;
  string description;
};

class Location {
public:
  string name;
  string description;
  vector<Object> objects;
};

vector<Location> locations = {
    {"office",
     "You are in your office and notice no one else is to be found.",
     {{"id", "Your ID card."}, {"key", "The key to your office."}}},
    {"hallway",
     "You are in the hallway. But you notice that one door has been left ajar. "
     "Room 237.",
     {{"note", "A note on the floor."}}},
    {"room 237",
     "You are in Room 237. It is empty except for a few pieces of furniture. "
     "But you notice a small object on the floor",
     {{"object", "A small, unidentified object."}}}

    /*    {"room 237", "You are in Room 237. It is empty except for a few pieces
       of furniture.",
            {{"key", "A small key."}}} */
};

int current_location = 0;
vector<string> inventory;

void show_help() {
  cout << "Available commands:" << endl;
  cout << " - look [room/object] : get a description of the room or a specific "
          "object"
       << endl;
  cout << " - get [object] : pick up an object in the current room" << endl;
  cout << " - drop [object] : drop an object from your inventory" << endl;
  cout << " - inventory : show the list of objects you are carrying" << endl;
  cout << " - go [direction] : move to a different room in the specified "
          "direction"
       << endl;
  cout << " - help : show this help message" << endl;
  cout << " - quit : exit the game" << endl;
}

void look(string noun) {
  if (noun == "") {
    cout << locations[current_location].description << endl;
    for (Object obj : locations[current_location].objects) {
      cout << "There is a " << obj.name << " here. " << obj.description << endl;
    }
  } else if (noun == "room") {
    cout << locations[current_location].description << endl;
  } else if (noun == "id") {
    if (current_location == 0) {
      cout << "Same picture from last year." << endl;
    }
  } else if (noun == "note") {
    if (current_location == 1) {
      cout << "The note reads: 'Don't go in there. -J'" << endl;
    } else {
      cout << "You don't see a note here." << endl;
    }
  } else {
    bool object_found = false;
    for (Object obj : locations[current_location].objects) {
      if (obj.name == noun) {
        cout << obj.description << endl;
        object_found = true;
        break;
      }
    }
    if (!object_found) {
      cout << "You don't see that here." << endl;
    }
  }
}
void get(string noun) {
  if (noun == "") {
    cout << "What do you want to get?" << endl;
  } else {
    // Check if the object exists in the current location
    bool found = false;
    for (int i = 0; i < locations[current_location].objects.size(); i++) {
      if (locations[current_location].objects[i].name == noun) {
        found = true;
        // Remove the object from the location's objects vector
        Object obj = locations[current_location].objects[i];
        locations[current_location].objects.erase(
            locations[current_location].objects.begin() + i);
        // Add the object to the player's inventory
        inventory.push_back(obj.name);
        // Print a message to the user
        cout << "You have obtained the " << obj.name << "." << endl;
        break;
      }
    }
    if (!found) {
      for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i] == noun) {
          cout << "You're already carrying the " << noun << "." << endl;
          return;
        }
      }
      cout << "You don't see that here." << endl;
    }
  }
}

void drop(string noun) {
  if (noun == "") {
    cout << "What do you want to drop?" << endl;
  } else {
    bool found = false;
    for (string obj : inventory) {
      if (obj == noun) {
        for (Object o : locations[current_location].objects) {
          if (o.name == obj) {
            cout << "You can't drop that here." << endl;
            found = true;
            break;
          }
        }
        if (!found) {
          locations[current_location].objects.push_back({obj, ""});
          cout << "You have dropped the " << obj << "." << endl;
        }
        // remove object from inventory
        for (int i = 0; i < inventory.size(); i++) {
          if (inventory.at(i) == noun) {
            inventory.erase(inventory.begin() + i);
            break;
          }
        }
        found = true;
        break;
      }
    }
    if (!found) {
      cout << "You're not carrying the " << noun << "." << endl;
    }
  }
}

void go(string noun) {
  if (noun == "") {
    cout << "Where do you want to go?" << endl;
  } else if (noun == "back") {
    if (current_location == 1) {
      cout << "You are back in your office." << endl;
      current_location = 0;
    }
  } else if (noun == "office") {
    cout << "You are in the office." << endl;
    current_location = 0;
  } else if (noun == "hallway") {
    cout << "You are in the hallway." << endl;
    current_location = 1;
  } else if (noun == "door") {
    cout
        << "You walked towards the open door, when suddenly you hear footsteps."
        << endl;
    current_location = 1;
  } else {
    cout << "You can't go there." << endl;
  }
}

void inventory_list() {
  if (inventory.empty()) {
    cout << "You're not carrying anything." << endl;
  } else {
    cout << "You are carrying: ";
    for (string item : inventory) {
      cout << item << " ";
    }
    cout << endl;
  }
}

int main() {
  cout << "Welcome employee 247." << endl;
  cout << "You are in your office and you notice that no else is to be found."
       << endl;
  cout << "You don't recall today being any particular holiday and no news "
          "that informed workers to not come to work."
       << endl;

  while (true) {
    string line;
    getline(cin, line);
    int f = line.find(" ");
    int l = line.rfind(" ");

    string verb = line.substr(0, f);
    string noun = line.substr(f + 1, line.back());

    if (line.find(" ") != line.rfind(" ")) {
      line.erase(f + 1, l - f);
      noun = line.substr(f + 1, line.length() - f - 1);
    } // code delete middle/unnecessary words

    if (noun == line) {
      noun = "";
    } // code NEED to prevent else statement from always printing!

    if (verb == "look") {
      look(noun);
    } else if (verb == "get") {
      get(noun);
    } else if (verb == "drop") {
      drop(noun);
    } else if (verb == "go") {
      go(noun);
    } else if (verb == "inventory") {
      inventory_list();
    } else if (verb == "help") {
      show_help();
    } else if (verb == "quit") {
      break;
    } else {
      cout << "You don't know how to do that." << endl;
    }
  }
} // end of main
