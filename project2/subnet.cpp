#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Convert IP string "a.b.c.d" to a 32-bit unsigned integer
unsigned int ipToInt(const string &ip) {
  unsigned int a, b, c, d;
  char dot;
  istringstream ss(ip);
  ss >> a >> dot >> b >> dot >> c >> dot >> d;
  return (a << 24) | (b << 16) | (c << 8) | d;
}

// Convert 32-bit unsigned integer to IP string
string intToIp(unsigned int ip) {
  return to_string((ip >> 24) & 0xFF) + "." + to_string((ip >> 16) & 0xFF) +
         "." + to_string((ip >> 8) & 0xFF) + "." + to_string(ip & 0xFF);
}

// Convert subnet mask to binary string
string maskToBinary(unsigned int mask) {
  string result;
  for (int i = 31; i >= 0; i--) {
    result += ((mask >> i) & 1) ? '1' : '0';
    if (i % 8 == 0 && i != 0)
      result += '.';
  }
  return result;
}

int main() {
  string networkIp;
  int originalPrefix, numSubnets;

  cout << "\nEnter Network Address (e.g. 211.12.180.0): ";
  cin >> networkIp;

  cout << "Enter Original Prefix Length (e.g. 24): ";
  cin >> originalPrefix;

  cout << "Enter Number of Subnets Required: ";
  cin >> numSubnets;

  // Calculate bits needed to borrow
  int bitsNeeded = (int)ceil(log2(numSubnets));
  int actualSubnets = (int)pow(2, bitsNeeded);

  // Adjust if user asked for exact power of 2
  if (actualSubnets < numSubnets) {
    bitsNeeded++;
    actualSubnets = (int)pow(2, bitsNeeded);
  }

  int newPrefix = originalPrefix + bitsNeeded;

  if (newPrefix > 30) {
    cout << "\nError: Not enough bits to create " << numSubnets << " subnets!"
         << endl;
    cout << "Maximum subnets possible: " << (int)pow(2, 30 - originalPrefix)
         << endl;
    return 1;
  }

  int hostBits = 32 - newPrefix;
  int totalAddressesPerSubnet = (int)pow(2, hostBits);
  int usableHostsPerSubnet = totalAddressesPerSubnet - 2;

  // Compute subnet mask
  unsigned int subnetMask = 0xFFFFFFFF << hostBits;
  unsigned int networkAddr = ipToInt(networkIp);

  // Ensure the network address is properly masked with original prefix
  unsigned int originalMask = 0xFFFFFFFF << (32 - originalPrefix);
  networkAddr = networkAddr & originalMask;

  cout << "\nGiven Network       : " << intToIp(networkAddr) << "/"
       << originalPrefix << endl;
  cout << "Original Subnet Mask: " << intToIp(originalMask) << endl;
  cout << "Subnets Requested   : " << numSubnets << endl;
  cout << "Bits Borrowed       : " << bitsNeeded << endl;
  cout << "Actual Subnets      : " << actualSubnets << endl;
  cout << "New Prefix Length   : /" << newPrefix << endl;
  cout << "New Subnet Mask     : " << intToIp(subnetMask) << endl;
  cout << "In Binary           : " << maskToBinary(subnetMask) << endl;
  cout << "Block Size          : " << totalAddressesPerSubnet << endl;
  cout << "Total Addresses/Sub : " << totalAddressesPerSubnet << endl;
  cout << "Usable Hosts/Sub    : " << usableHostsPerSubnet << endl;
  cout << "Total Usable Hosts  : " << usableHostsPerSubnet * actualSubnets
       << endl;

  // IP class detection
  unsigned int firstOctet = (networkAddr >> 24) & 0xFF;
  string ipClass;
  if (firstOctet <= 127)
    ipClass = "A";
  else if (firstOctet <= 191)
    ipClass = "B";
  else if (firstOctet <= 223)
    ipClass = "C";
  else if (firstOctet <= 239)
    ipClass = "D (Multicast)";
  else
    ipClass = "E (Reserved)";
  cout << "IP Class            : Class " << ipClass << endl;

 cout << left << setw(8) << "Subnet" << setw(20) << "Network Addr" << setw(20)
       << "First Usable" << setw(20) << "Last Usable" << setw(20) << "Broadcast"
       << endl;

  cout << string(88, '-') << endl;

  for (int i = 0; i < actualSubnets; i++) {
    unsigned int subnetStart = networkAddr + (i * totalAddressesPerSubnet);
    unsigned int firstUsable = subnetStart + 1;
    unsigned int lastUsable = subnetStart + totalAddressesPerSubnet - 2;
    unsigned int broadcast = subnetStart + totalAddressesPerSubnet - 1;

    cout << left << setw(8) << (i + 1) << setw(20) << intToIp(subnetStart)
         << setw(20) << intToIp(firstUsable) << setw(20) << intToIp(lastUsable)
         << setw(20) << intToIp(broadcast) << endl;
  }
  return 0;
}
