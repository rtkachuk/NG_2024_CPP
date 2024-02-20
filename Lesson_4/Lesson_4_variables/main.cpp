#include <iostream>

using namespace std;

class Temperature {
public:
    Temperature() { m_temperature = 0; }
    Temperature(int temp) { if (setTemperature(temp) == false) { setTemperature(0); } }

    bool setTemperature(int temp) {
        if (temp < -50 || temp > 50) {
            return false;
        }
        m_temperature = temp;
        return true;
    }
    int getTemperature() { return m_temperature; }

private:
    int m_temperature;
};

int main()
{
    Temperature krop;
    cout << "Krop temperature: " << krop.getTemperature() << endl;
    Temperature kyiv(5);
    cout << "Kyiv temperature: " << kyiv.getTemperature() << endl;
    Temperature test;
    if (test.setTemperature(-100) == false) {
        cout << "Invalid temperature provided!" << endl;
    }
    return 0;
}
