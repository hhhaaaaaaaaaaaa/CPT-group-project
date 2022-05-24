#include<iostream>
using namespace std;
#include<string>
#include<fstream>
class AirPlane
{
public:
	AirPlane() {
		len = 0; isUsed= false;
	}
	string id;
	int type;
	int**site;
	int len;
	bool isUsed;
};
class Flight
{
public:
	string id;
	AirPlane airPlane;
	string start;
	string destination;
	string startTime;
	string endTime;
	double money;
};
class Passenger
{
public:
	string name;
	string flightId;
	int siteNum;
};
class Manager
{
public:
	Manager() 
	{ 
		apLen = fLen = passengerLen = 0; readAirPlane(); readFlight();
		for (int i = 0; i < fLen; i++)
		{
			for (int j = 0; j < apLen; j++)
			{
				if (f[i].airPlane.id == ap[j].id)
				{
					f[i].airPlane = ap[j];
					break;
				}
			}
		}
		readPassenger();
	}
	AirPlane ap[20];
	int apLen;
	Flight f[10];
	int fLen;
	Passenger passenger[500];
	int passengerLen;
public:
	void menuLogin();
	void actionLogin();

	void menuMain();
	void actionMain();

	void menuAirPlane();
	void actionAirplane();
	void addAirPlane();
	bool airIdIsexist(string id);
	void modifyPlane();
	void deletePlane();
	void showAllPlane();
	void readAirPlane();
	void saveAirPlane();

	void menuFlight();
	void actionFlight();
	void addFlight();
	void modifyFlight();
	void deleteFlight();
	void showAllFlight();
	void readFlight();
	void saveFlight();

	void menuPassenger();
	void actionPassenger();
	void booking();
	void refund();
	void selectFlight();
	void readPassenger();
	void writePassenger();

	void statics();
	void calPeriodTickets();
};
void Manager::calPeriodTickets()
{
	string start;
	cout << "Please enter the start time: ";
	cin >> start;
	cout << "Please enter the end time: ";
	string end;
	cin >> end;
	int cnt = 0;
	for (int i = 0; i < passengerLen; i++)
	{
		for (int j = 0; j< fLen; j++)
		{
			if (passenger[i].flightId == f[j].id)
			{
				if (f[j].startTime > start && f[j].startTime < end)
				{
					cnt++;
				}
			}
		}
	}
	cout << cnt << " tickets were sold." << endl;
}
void Manager::statics()
{
	int cnt_1=0, cnt_2=0;
	for (int i = 0; i < apLen; i++)
	{
		if (ap[i].type == 1)
			cnt_1++;
		else cnt_2++;
	}
	cout << "The number of P62 airplane:" << cnt_1 << endl;
	cout << "The number of P124 airplane: " << cnt_2 << endl;
	for (int i = 0; i < fLen; i++)
	{
		cout << "Flight ID: "<<f[i].id<<", number of passenger: " << f[i].airPlane.len << endl;
		cout << "Total income: " << f[i].airPlane.len * f[i].money << endl;
	}

}
void Manager::readPassenger()//Read information of passengers
{
	ifstream ifs;
	ifs.open("passenger.txt");
	if (!ifs)
		return;
	while (!ifs.eof())
	{
		ifs >> passenger[passengerLen].name;
		if (ifs.eof())
			break;
		ifs>> passenger[passengerLen].flightId >> passenger[passengerLen].siteNum;
		passengerLen++;
	}
	ifs.close();
}
void Manager::writePassenger()//Write information of passengers
{
	ofstream ofs;
	ofs.open("passenger.txt");
	for (int i = 0; i < passengerLen; i++)
	{
		ofs << passenger[i].name << " " << passenger[i].flightId << " " << passenger[i].siteNum << endl;
	}
	ofs.close();
}
void Manager ::menuLogin()//Log-in 
{
	system("cls");
	cout << "       Aviation Management System" << endl;
	cout << "       1:Log in as administrator" << endl;
	cout << "       2:Log in as passenger" << endl;
	cout << "       0:Exit" << endl;
	cout << "       Please enter your choice:" << endl;
}
void Manager ::actionLogin()//verification
{
	int ch;
	while (1)
	{
		menuLogin();
		cin >> ch;
		switch (ch)
		{
		case 1:actionMain();//administrator
			break;
		case 2:actionPassenger();//passenger
			break;
		case 0:
			return;
			break;
		default:
			cout << "Wrong input!" << endl;
			break;
		}
		system("pause");
	}
}
void Manager::menuMain()//menu
{
	system("cls");
	cout << "       Aviation Management System" << endl;
	cout << "       1:Airplane management" << endl;
	cout << "       2:Flight management" << endl;
	cout << "       3:Passenger management" << endl;
	cout << "       4:Statistics" << endl;
	cout << "       0:Return to previous page" << endl;
	cout << "       Please enter your choice:" << endl;
}
void Manager::actionMain()//verification of main
{
	int ch;
	while (1)
	{
		menuMain();
		cin >> ch;
		switch (ch)
		{
		case 1:actionAirplane();//Airplane management
			break;
		case 2:actionFlight();//Flight management
			break;
		case 3:actionPassenger();//Passenger management
			break;
		case 4:
			statics();//Statistics
			break;
		case 0:
			return;
			break;
		default:
			cout << "Wrong input!" << endl;
			break;
		}
		system("pause");
	}
}
int main()
{
	Manager m;
	m.actionLogin();


	return 0;
}

void Manager::menuAirPlane()
{
	system("cls");
	cout << "       Airplane Management System" << endl;
	cout << "       1:Add airplane's information" << endl;
	cout << "       2:Edit aieplane's information" << endl;
	cout << "       3:Remove airplane's information" << endl;
	cout << "       4:Show airplane's information" << endl;
	cout << "       0:Return to previous page" << endl;
	cout << "       Please enter your choice:" << endl;
}
void Manager::actionAirplane()//verification
{
	int ch;
	while (1)
	{
		menuAirPlane();
		cin >> ch;
		switch (ch)
		{
		case 1:addAirPlane();//1
			break;
		case 2:modifyPlane();//2
			break;
		case 3:deletePlane();//3
			break;
		case 4:showAllPlane();//4
			break;
		case 0:
			return;
			break;
		default:
			cout << "Wrong input!"  << endl;
			break;
		}
		system("pause");
	}
}
bool Manager::airIdIsexist(string id)//identify if the plane exists
{
	for (int i = 0; i < apLen; i++)
	{
		if (id == ap[i].id)
		{
			return true;
		}
	}
	return false;
}
void Manager::addAirPlane()
{
	if (apLen >= 20)
	{
		cout << "The upper limit of airplane has been reached!" << endl;
		return;
	}
	cout << "Please enter the number of airplane";
	cin >> this->ap[apLen].id;
	if (airIdIsexist(ap[apLen].id))
	{
		cout << "The number already exists!" << endl;
		return;
	}
	cout << "Please enter the type(1:P62, 2:P124): ";
	cin >> ap[apLen].type;
	if (ap[apLen].type == 1)//add seats' information
	{
		ap[apLen].site = new int* [6];
		for (int i = 0; i < 6; i++)
		{
			ap[apLen].site[i] = new int[2];
			for (int j = 0; j < 2; j++)
				ap[apLen].site[i][j] = 0;
		}
		ap[apLen].len = 0;
	}
	else if (ap[apLen].type == 2)
	{
		ap[apLen].site = new int* [12];
		for (int i = 0; i < 12; i++)
		{
			ap[apLen].site[i] = new int[4];
			for (int j = 0; j < 4; j++)
				ap[apLen].site[i][j] = 0;
		}
		ap[apLen].len = 0;
	}
	ap[apLen].isUsed = false;
	apLen++;
	cout << "Successfully added!" << endl;
	saveAirPlane();//save
}
void Manager::modifyPlane()//change planes' information
{
	string id;
	cout << "Please enter the number: ";
	cin >> id;
	for (int i = 0; i < apLen; i++)
	{
		if (id == ap[i].id)
		{
			string newId;
			ap[i].id = "";//empty the former id
			cout << "Please enter the new id: ";
			cin >> newId;
			while (airIdIsexist(newId))
			{
				cout << "The number already exists!" << endl;
				cout << "Please enter the new id: ";
				cin >> newId;
			}
			ap[i].id=newId;
			//renew the id
			for (int j = 0; j < fLen; j++)
			{
				if (f[j].airPlane.id == id)
				{
					f[j].airPlane.id = newId;
					break;
				}
			}
			cout << "Successfully modified!\n";
			saveAirPlane();//save
			return;
		}
	}
	cout << "The number cannot be found" << endl;
	cout<< "Modification failed!" << endl;
}
void Manager::deletePlane()//delete airplane
{
	string id;
	cout << "Please enter the number:";
	cin >> id;
	for (int i = 0; i < apLen; i++)
	{
		if (id == ap[i].id)
		{
			//modify the corresponding flight
			for (int j = 0; j < fLen; j++)
			{
				if (ap[i].id == f[j].airPlane.id)
				{

					//delete the passengers
					for (int k = 0; k < passengerLen; k++)
					{
						if (passenger[k].flightId == f[i].id)
						{
							for(;k<passengerLen-1;k++)
							passenger[k] = passenger[k + 1];
							passengerLen--;
							k = -1;
						}
					}

					f[j].airPlane.id = "null";//empty the id
					f[j].airPlane.len = 0;
				}
			}
			
			for (; i < apLen - 1; i++)
			{
				ap[i] = ap[i + 1];
			}
			apLen--;
			cout << "Successfully deleted!\n";
			saveAirPlane();//save
			saveFlight();
			writePassenger();
			return;
		}
	}
	cout << "The number cannot be found" << endl;
	cout << "Deletion failed!" << endl;
}
void Manager::readAirPlane()
{
	ifstream ifs;
	ifs.open("airplane.txt");
	if (!ifs)
		return;
	while (!ifs.eof())
	{
		ifs >> ap[apLen].id;
		if (ifs.eof())
			break;

		ifs>> ap[apLen].type >> ap[apLen].isUsed >> ap[apLen].len;
		if (ap[apLen].type == 1)//add seats
		{
			ap[apLen].site = new int* [6];
			for (int i = 0; i < 6; i++)
			{
				ap[apLen].site[i] = new int[2];
				for (int j = 0; j < 2; j++)
					ifs>>ap[apLen].site[i][j] ;
			}
		}
		else if (ap[apLen].type == 2)
		{
			ap[apLen].site = new int* [12];
			for (int i = 0; i < 12; i++)
			{
				ap[apLen].site[i] = new int[4];
				for (int j = 0; j < 4; j++)
					ifs >> ap[apLen].site[i][j];
			}
		}
		apLen++;
	}
	ifs.close();
}
void Manager::saveAirPlane()//save
{
	ofstream ofs;
	ofs.open("airplane.txt");
	for (int i = 0; i < apLen; i++)
	{
		ofs << ap[i].id << "\t" << ap[i].type << "\t" << ap[i].isUsed << '\t' << ap[i].len << endl;
		if (ap[i].type == 1)
		{
			for (int j = 0; j < 6; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					ofs << ap[i].site[j][k]<<" ";
				}
			}
			ofs << endl;
		}
		else
		{
			for (int j = 0; j < 12; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					ofs << ap[i].site[j][k] << " ";
				}
			}
			ofs << endl;
		}
	}
	ofs.close();
}
void Manager::showAllPlane()//show all the information
{
	cout << "number\t type\t remaining seats" << endl;
	for (int i = 0; i < apLen; i++)
	{
		cout << ap[i].id << "\t";
		if (ap[i].type == 1)
		{
			cout << "p62" << "\t";
			cout <<12- ap[i].len << endl;
		}
		else
		{
			cout << "p124" << "\t";
			cout << 48 - ap[i].len << endl;
		}
		
	}
}


void Manager::menuFlight()//manage the flight
{
	system("cls");
	cout << "       Flight Management System" << endl;
	cout << "       1:Add flight's information" << endl;
	cout << "       2:Edit flight's information" << endl;
	cout << "       3:Remove flight's information" << endl;
	cout << "       4:Show flight's information" << endl;
	cout << "       0:Return to previous page" << endl;
	cout << "       Please enter your choice:" << endl;
}
void Manager::actionFlight()
{
	int ch;
	while (1)
	{
		menuFlight();
		cin >> ch;
		switch (ch)
		{
		case 1:addFlight();//1
			break;
		case 2:modifyFlight();//2
			break;
		case 3:deleteFlight();//3
			break;
		case 4:showAllFlight();//4
			break;
		case 0:
			return;
			break;
		default:
			cout << "Wrong inputs!" << endl;
			break;
		}
		system("pause");
	}
}
void Manager::addFlight()
{
	if (fLen >= 10)
	{
		cout << "The number of flights is full" << endl;
		return;
	}
	if (apLen == 0)
	{
		cout << "No planes! Flights cannot be added!࣡" << endl;
		return;
	}

	bool isHave = false;
	for (int i = 0; i < apLen; i++)//to see if the plane is free
	{
		if (ap[i].isUsed == false)
		{
			isHave = true;
			break;
		}
	}
	if (!isHave)//if no plane is free
	{
		cout << "No plane is free!" << endl;
		return;
	}
	cout<<"Flight number: ";
	cin >> f[fLen].id;
	for (int i = 0; i < fLen; i++)
	{
		if (f[i].id == f[fLen].id)//if number has existed
		{
			cout << "The number already exists!" << endl;
			return;
		}
	}
	while (1)
	{
		bool isExit = false;
		bool isUsed = false;
		cout << "ִID of airplane of this flight: ";
		string idd;
		cin >> idd;
		for (int i = 0; i < fLen; i++)
		{
			if (idd == f[i].airPlane.id)//if the plane has been used by other flights
			{
				isUsed = true;
				break;
			}
		}
		if (isUsed)
		{
			cout << "The airplane has been used!" << endl;
			cout << "Please enter another number!" << endl;
			continue;
		}
		for (int i = 0; i < apLen; i++)
		{
			if (idd == ap[i].id)//if the plane is correct
			{
				f[fLen].airPlane = ap[i];//let the plane be the entered plane
				ap[i].isUsed = true;
				isExit = true;
				break;
			}
		}
		if (!isExit)
		{
			cout << "The number doesn't exist!" << endl;
			cout << "Please enter another number!" << endl;
			continue;
		}
		else
			break;
	}
	cout<<"Place of departure: ";
	cin >> f[fLen].start;
	cout<<"Terminal: ";
	cin >> f[fLen].destination;
	cout<<"Start time: ";
	cin >> f[fLen].startTime;
	cout<<"End time: ";
	cin >> f[fLen].endTime;
	cout<<"Ticket price: ";
	cin >> f[fLen].money;
	fLen++;
	cout << "Successfully added!" << endl;
	saveAirPlane();
	saveFlight();
}
void Manager::modifyFlight()//modify
{
	string id;
	cout << "Please enter the number of the flight to be modified: ";
	cin >> id;
	for (int i = 0; i < fLen; i++)
	{
		if (id == f[i].id)//if exists
		{
			cout << "Please enter the modified information: " << endl;
			cout << "New flight number: ";
			cin >> f[i].id;
			//renew passengers' information
			for (int j = 0; j < passengerLen; j++)
			{
				if (passenger[j].flightId == id)
				{
					passenger[j].flightId = f[i].id;
				}
			}
			bool isHave = false;
			for (int i = 0; i < apLen; i++)//if there is free airplane
			{
				if (ap[i].isUsed == false)
				{
					isHave = true;
					break;
				}
			}
			if(isHave)
			while (1)
			{
				bool isExit = false;
				bool isUsed = false;
				cout << "ִThe plane ID； ";
				string idd;
				cin >> idd;

				if (idd == f[i].airPlane.id)//if id exists
					break;
				for (int j = 0; j < fLen; j++)//if id doesn't exist
				{
					if (idd == f[j].airPlane.id)
					{
						isUsed = true;
						break;
					}
				}
				if (isUsed)
				{
					cout << "The airplane is being used!" << endl;
					cout << "Please enter another number!" << endl;
					continue;
				}

				for (int j = 0; j < apLen; j++)
				{
					if (idd == ap[j].id)//if id exists
					{
						for (int k = 0; k < apLen; k++)
						{
							if (f[i].airPlane.id == ap[k].id)
							{
								ap[k].isUsed = false;
								break;
							}
						}
						f[i].airPlane = ap[j];
						ap[j].isUsed=true;
						isExit = true;
					}
				}
				if (!isExit)
				{
					cout << "The airplane is being used!" << endl;
					cout << "Please enter another number!" << endl;
					continue;
				}
				else
					break;
			}
			cout << "Place of departure: ";
			cin >> f[i].start;
			cout << "Terminal: ";
			cin >> f[i].destination;
			cout << "Start time: ";
			cin >> f[i].startTime;
			cout << "End time:";
			cin >> f[i].endTime;
			cout << "Ticket price: ";
			cin >> f[i].money;
			cout << "Successfully modified!" << endl;
			saveAirPlane();
			saveFlight();
			writePassenger();
			return;
		}
	}
	cout << "�޸�ʧ�ܣ�" << endl;
}
void Manager::deleteFlight()
{
	string id;
	cout << "Please enter the flight number to be deleted: ";
	cin >> id;
	for (int i = 0; i < fLen; i++)
	{
		if (id == f[i].id)//if exists
		{
			for (int j = 0; j < apLen; j++)
			{
				if (f[i].airPlane.id == ap[j].id)
				{
					ap[j].isUsed = false;
					if (ap[j].type == 1)
					{
						for (int x = 0; x < 6; x++)
						{
							for (int y = 0; y < 2; y++)
							{
								ap[j].site[x][y] = 0;
							}
						}
						ap[j].len = 0;
					}
					else if (ap[j].type == 2)
					{
						for (int x = 0; x < 12; x++)
						{
							for (int y = 0; y < 4; y++)
							{
								ap[j].site[x][y] = 0;
							}
						}
						ap[j].len = 0;
					}
				}
			}
			for (int j = 0; j < passengerLen; j++)
			{
				if (passenger[j].flightId == f[i].id)
				{
					for (; j < passengerLen-1; j++)
					{
						passenger[j] = passenger[j + 1];
					}
					passengerLen--;
					j =-1;
				}
			}
			for (; i < fLen - 1; i++)
			{
				f[i] = f[i + 1];
			}
			fLen--;
			cout << "Successfully deleted!" << endl;
			saveAirPlane();
			saveFlight();
			return;
		}
	}
	cout << "Deletion failed!" << endl;
}
void Manager::readFlight()
{
	ifstream ifs;
	ifs.open("flight.txt");
	if (!ifs)
		return;
	while (!ifs.eof())
	{
		ifs>> f[fLen].id>>f[fLen].airPlane.id >> f[fLen].start>> f[fLen].destination
			>> f[fLen].startTime >> f[fLen].endTime >>f[fLen].money ;
		if (ifs.eof())
			break;
		fLen++;
	}
	ifs.close();
}
void Manager::saveFlight()
{
	ofstream ofs;
	ofs.open("flight.txt");
	for (int i = 0; i < fLen; i++)
	{
		ofs << f[i].id << "\t" << f[i].airPlane.id << "\t" << f[i].start << "\t" << f[i].destination
			<< "\t" << f[i].startTime << "\t" << f[i].endTime << "\t" << f[i].money << endl;
	}
	ofs.close();
}
void Manager::showAllFlight()
{
	cout << "Flight number\tִ Airplane ID\t Place of departure\t Terminal\t Start time\t End time\t Ticket price"<<endl;
	for (int i = 0; i < fLen; i++)
	{
		cout<< f[i].id<<"\t"<<f[i].airPlane.id<<"\t"<<f[i].start<<"\t"<<f[i].destination
			<<"\t"<<f[i].startTime<<"\t"<<f[i].endTime<<"\t"<<f[i].money<<endl;
	}
}

void Manager::menuPassenger()
{
	system("cls");
	cout << "       Passenger Management System" << endl;
	cout << "       1:Book a ticket" << endl;
	cout << "       2:Return a ticket" << endl;
	cout << "       3:Query flight information" << endl;
	cout << "       0:Return to previous page" << endl;
	cout << "       Please enter your choice:" << endl;
}
void Manager::actionPassenger()
{
	int ch;
	while (1)
	{
		menuPassenger();
		cin >> ch;
		switch (ch)
		{
		case 1:booking();//1
			break;
		case 2:refund();//2
			break;
		case 3:selectFlight();//3
			break;
		case 0:
			return;
			break;
		default:
			cout << "Wrong input!" << endl;
			break;
		}
		system("pause");
	}
}
void Manager::booking()//book
{
	if (passengerLen >= 500)
	{
		cout << "The passenger number is full!" << endl;
		return;
	}
	cout<<"Please enter your name: ";
	cin >> passenger[passengerLen].name;
	string start, end;
	cout << "Please enter the start place: ";
	cin >> start;
	cout << "Please enter the terminal: ";
	cin >> end;
	int cnt = 0;//the number of search
	cout << "These flights meet the conditions: " <<endl;
	cout << "Flight number\t Start time\t End time\t Price\t Airplane type\t Remaining seats" << endl;
	for (int i = 0; i < fLen; i++)//search for the flights
	{
		if (f[i].start == start && f[i].destination == end)
		{
			cnt++;
			cout << f[i].id << "\t" << f[i].startTime << "\t" << f[i].endTime << "\t" << f[i].money<<"\t" << endl;

			if (f[i].airPlane.type == 1)
			{
				cout << "P62\t" <<12-f[i].airPlane.len<< endl;
			}
			else
				cout << "P124\t" << 48 - f[i].airPlane.len << endl;
		}
	}
	if (cnt == 0)
	{
		cout << "No such flights!" << endl;
		return;
	}
	string id2;
	cout<<"Please enter the flight number";
	cin >> id2;
	for (int i = 0; i < fLen; i++)//search for flights
	{
		if (f[i].start == start && f[i].destination == end && f[i].id == id2)//if exists
		{
			if (f[i].airPlane.id == "null")
			{
				cout << "No such flights!" << endl;
				return;
			}
			//Seearch if someone has bought tickets that has changed the time
			for (int x = 0; x < passengerLen; x++)
			{
				if (passenger[x].name == passenger[passengerLen].name)//if the same person, judge if the ticket is repetitive
				{
					if (passenger[x].flightId == id2)
					{
						cout << "You have bought the ticket in this time period." << endl;
						return;
					}
				}
			}
			if (f[i].airPlane.type == 1)
			{
				if (f[i].airPlane.len >= 12)//if seats are full
				{
					cout << "Sorry, there are no empty seats." << endl;
					cout << "Booking failed!" << endl;
				}
				else
				{
					cout << "Successfully booked!" << endl;
					passenger[passengerLen].flightId = id2;//flight number
					for (int k = 0; k < 6; k++)
					{
						for (int j = 0; j < 2; j++)
						{
							if (f[i].airPlane.site[j][k] == 0)
							{
								passenger[passengerLen++].siteNum = k*2+j+1;//seat number
								f[i].airPlane.site[j][k] = 1;
								f[i].airPlane.len++;
								for (int k = 0; k < apLen; k++)//renew seats
								{
									if (f[i].airPlane.id == ap[k].id)
									{
										ap[k] = f[i].airPlane;
										break;
									}
								}
								
								saveAirPlane();
								writePassenger();
								saveFlight();
								return;
							}
						}
					}

				}
			}
			else if (f[i].airPlane.type == 2)
			{
				if (f[i].airPlane.len >= 48)//no seats
				{
					cout << "Sorry, there are no empty seats." << endl;
					cout << "Booking failed!" << endl;
				}
				else
				{
					cout << "Successfully booked!" << endl;
					passenger[passengerLen].flightId = id2;//flight number
					for (int k = 0; k < 12; k++)
					{
						for (int j = 0; j < 4; j++)
						{
							if (f[i].airPlane.site[j][k] == 0)
							{
								passenger[passengerLen++].siteNum = 4 * k + j + 1;//seat number
								f[i].airPlane.len++;
								for (int k = 0; k < apLen; k++)//renew seats
								{
									if (f[i].airPlane.id == ap[k].id)
									{
										ap[k] = f[i].airPlane;
										break;
									}
								}
								
								saveAirPlane();
								writePassenger();
								saveFlight();
								return;
							}
						}
					}
				}
			}
			return;
		}
	}
	cout << "Not found!" << endl;

}
void Manager::refund()//feturn the ticket
{
	string name;
	cout << "Please enter your name:";
	cin >> name;
	for (int i = 0; i < passengerLen; i++)
	{
		if (passenger[i].name == name)//if there is repetitive name
		{
			//delete the booked seat
			for (int j = 0; j < fLen; j++)
			{
				if (f[j].id == passenger[i].flightId)//if there is repetitive flight
				{
					if (f[j].airPlane.type == 1)//if P62
					{
						int x = passenger[i].siteNum % 2 == 0 ? passenger[i].siteNum / 2 - 1 : passenger[i].siteNum / 2;
						int y = passenger[i].siteNum % 2 == 0 ? 1 : 0;
						f[j].airPlane.site[x][y] = 0;//empty the seat
						f[j].airPlane.len--;//seat number -1
						for (int k = 0; k < apLen; k++)//renew the seats
						{
							if (f[i].airPlane.id == ap[k].id)
							{
								ap[k] = f[i].airPlane;
								break;
							}
						}
						break;
					}
					else if (f[j].airPlane.type == 2)//if P124
					{
						int x = passenger[i].siteNum % 4 == 0 ? passenger[i].siteNum / 4 - 1 : passenger[i].siteNum / 4;
						int y = passenger[i].siteNum % 4 == 0 ? 3 : passenger[i].siteNum % 4-1;
						f[j].airPlane.site[x][y] = 0;//empty
						f[j].airPlane.len--;
						for (int k = 0; k < apLen; k++)//seat number -1
						{
							if (f[i].airPlane.id == ap[k].id)
							{
								ap[k] = f[i].airPlane;
								break;
							}
						}
						break;
					}
				}
			}
			
			//delete passenger's information
			for (; i < passengerLen - 1; i++)//delete
			{
				passenger[i] = passenger[i + 1];
			}
			passengerLen--;
			cout << "Successfully refunded" << endl;
			writePassenger();
			saveAirPlane();
			saveFlight();
			return;
		}
	}
	cout << "Fail to refund!" << endl;
}
void Manager::selectFlight()//search for sepecific flight
{
	cout << "Please enter the flight number: ";
	string id;
	cin >> id;
	for (int i = 0; i < fLen; i++)
	{
		if (id == f[i].id)
		{
			if (f[i].airPlane.id == "null")
			{
				cout << "No flights!" << endl;
				return;
			}
			cout << "Flight ID\t Start time\t End time\t Price\t Plane type\t remaining seats" << endl;

			cout << f[i].id << "\t" << f[i].startTime << "\t" << f[i].endTime << "\t" << f[i].money << "\t" << endl;

			if (f[i].airPlane.type == 1)//if same//1:P62,2:P124
			{
				cout << "P62\t" << 12 - f[i].airPlane.len << endl;
			}
			else
				cout << "P124\t" << 48 - f[i].airPlane.len << endl;
			return;
		}
	}
	cout << "Not found!" << endl;
}