#include "Database.h"

Database::Entry::Entry(const char * entry, int val, Field::Mode in_mode)
	:
	value(val),
	mode(in_mode)
{
	stringcopy(entry,this->name,sizeof(this->name));
}


void Database::Entry::Print(Graphics& gfx,const PixelFont& font,const Vei2& pos) const
{ 
	Vei2 intern = pos;
	std::string printname = name,printvalue = std::to_string(value);
	font.DrawString(intern, printname,gfx,2,Colors::Green);
	intern.x += 324;
	font.DrawString(intern, printvalue, gfx, 2, Colors::Green);
}

void Database::Entry::Serialize(std::ofstream & out) const
{
	out.write(name, sizeof(name));
	out.write(reinterpret_cast<const char*> (&value), sizeof(value));
	out.write(reinterpret_cast<const char*> (&mode), sizeof(mode));
}

void Database::Entry::Deserialize(std::ifstream & in)
{
	in.read(name, sizeof(name));
	in.read(reinterpret_cast<char*> (&value), sizeof(value));
	in.read(reinterpret_cast<char*> (&mode), sizeof(mode));
}

int Database::Entry::GetValue() const
{
	return value;
}


Field::Mode Database::Entry::GetDatabaseMode() const
{
	return mode;
}

void Database::Entry::stringcopy(const char * pSrc, char * pDst, int maxsize)
{
	int n = 0;
	for (; *pSrc!= 0&&(n+1<maxsize); pSrc++, pDst++) {
		*pDst = *pSrc;
		n++;
	}
	*pDst = 0;
}


void Database::Load(const char * filename)
{
	std::ifstream in(filename, std::ios::binary);
	int nEntries;
	in.read(reinterpret_cast<char*>(&nEntries), sizeof(nEntries));
	entries.resize(nEntries);
	for (auto& e : entries) {
		e.Deserialize(in);
	}
}

void Database::Save(const char * filename)
{
	int ecountClassic = 0, ecountMouse = 0, ecountNum = 0;
	std::stable_sort(entries.begin(), entries.end());
	for (size_t i = 0;i<entries.size();i++) {
		switch (entries[i].GetDatabaseMode()) {
		case Field::Mode::Classic:
			ecountClassic++;
 			if (ecountClassic > 5) { entries.erase(entries.begin()+i);
			i--;
			}
			break;
		case Field::Mode::Mouse:
			ecountMouse++;
			if (ecountMouse > 5) {
				entries.erase(entries.begin() + i);
				i--;
			}
			break;
		case Field::Mode::NumPad:
			ecountNum++;
			if (ecountNum > 5) {
				entries.erase(entries.begin() + i);
				i--;
			}
			break;
		}
	}
	std::ofstream out(filename, std::ios::binary);
	const int size = int(entries.size());
	out.write(reinterpret_cast<const char*>(&size), sizeof(size));
	
	for (const Entry& e : entries) {
		e.Serialize(out);
	}
}

void Database::Print(Graphics& gfx, const Vei2& pos, const PixelFont& font, Field::Mode mode) const
{
	Vei2 update_pos = pos;
	
	font.DrawString(update_pos, "highscores", gfx, 4, Colors::Green);	
	update_pos.y += 60;
	switch (mode) {
	case Field::Mode::Classic:
		update_pos.x += 75;
		font.DrawString(update_pos, "classic", gfx, 3, Colors::Green);
		update_pos.x -= 75;
		break;
	case Field::Mode::Mouse:
		update_pos.x += 90;
		font.DrawString(update_pos, "mouse", gfx, 3, Colors::Green);
		update_pos.x -= 90;
		break;
	case Field::Mode::NumPad:
		update_pos.x += 75;
		font.DrawString(update_pos, "numpad", gfx, 3, Colors::Green);
		update_pos.x -= 75;
		break;
	}
	update_pos.y += 72;
	for (const Entry&e : entries) {
		if (e.GetDatabaseMode() == mode) {
			e.Print(gfx, font, update_pos);
			update_pos.y += 24;
		}
	}
}

void Database::Add(const char* name, int value,Field::Mode in_mode)
{
	entries.emplace_back(name, value,in_mode);
}

bool Database::CheckIfHighscore(int newvalue, Field::Mode in_mode)
{
	int entrycounter = 0;
	for (const Entry& e : entries) {
		if (e.GetDatabaseMode() == in_mode) {
			entrycounter++;
		};
	}
	if (entrycounter <5) {
		return true;
	}
	else {
		bool returnval = false;
		for (const Entry& e : entries) {
			if (e.GetDatabaseMode() == in_mode) {
				returnval = returnval || (newvalue > e.GetValue());
			}
		}
		return returnval;
	}
}
