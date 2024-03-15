#include "WardenFort.h"
#include <QApplication>
#include <QThread>
#include <winsock2.h> // For Windows Sockets
#include <ws2tcpip.h> // For TCP header structure
#include <limits>

// Include Npcap headers
#include <pcap.h>
int i = 0;
// Define TCP header flags for Windows
#define TH_FIN  0x01
#define TH_SYN  0x02
#define TH_RST  0x04
#define TH_PUSH 0x08
#define TH_ACK  0x10
#define TH_URG  0x20

constexpr int MAX_EXPECTED_PAYLOAD_LENGTH = 1500; // Maximum expected payload length
constexpr int MIN_EXPECTED_PAYLOAD_LENGTH = 0;    // Minimum expected payload length (can be adjusted as needed)

struct my_tcphdr {
    u_short th_sport;  // source port
    u_short th_dport;  // destination port
    u_int th_seq;      // sequence number
    u_int th_ack;      // acknowledgement number
    u_char th_offx2;   // data offset, rsvd
    u_char th_flags;
    u_short th_win;     // window
    u_short th_sum;     // checksum
    u_short th_urp;     // urgent pointer
};

bool isFilteredAdapter(pcap_if_t* adapter) {
    // Check if adapter is a WAN miniport or VirtualBox adapter by description
    if (adapter->description) {
        QString description = QString(adapter->description).toLower();
        if (description.contains("wan miniport") || description.contains("virtualbox"))
            return true;
    }

    // Check if adapter is a loopback adapter (npf_loopback)
    if (adapter->flags & PCAP_IF_LOOPBACK)
        return true;

    // Check if adapter is inactive
    if (!(adapter->flags & PCAP_IF_CONNECTION_STATUS_CONNECTED))
        return true;

    return false;
}

void analyzeTCPPacket(const u_char* packet, int packetLength, WardenFort& wardenFort) {
    

    // Ensure the packet is large enough to contain a TCP header
    if (packetLength < sizeof(struct my_tcphdr)) {
        qDebug() << "Packet is too small to contain TCP header";
        return;
    }

    // Extract TCP header from packet
    const struct my_tcphdr* tcpHeader = reinterpret_cast<const struct my_tcphdr*>(packet);

    // Calculate TCP header length
    int tcpHeaderLength = (tcpHeader->th_offx2 >> 4) * 4;

    // Calculate payload length
    int payloadLength = packetLength - tcpHeaderLength;

    // Analyze payload length
    if (payloadLength > MAX_EXPECTED_PAYLOAD_LENGTH) {
        i++;
        qDebug() << "Suspiciously long payload detected!";
        qDebug() << i;
        wardenFort.setLabelText(QString::number(i) + " Threat");
        // Take appropriate action, such as logging or alerting
        
    }
    else if (payloadLength < MIN_EXPECTED_PAYLOAD_LENGTH) {
        qDebug() << "Suspiciously short payload detected!";
        // Take appropriate action, such as logging or alerting
    }

    // Analyze TCP flags
    if (tcpHeader->th_flags & TH_SYN && !(tcpHeader->th_flags & TH_ACK)) {
        qDebug() << "THREAT ALERT: SYN packet without ACK detected!";
        // You may want to implement threatCounter and syn_count here
    }
    else {
        // Reset SYN packet counter for non-SYN packets
        // syn_count = 0; // Uncomment this line if syn_count is declared and defined elsewhere
    }

    // Analyze other aspects of the TCP packet as needed
    // For example, you could check sequence numbers, window size, etc.
}

void packetHandler(u_char* userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
    WardenFort& wardenFort = *reinterpret_cast<WardenFort*>(userData);
    qDebug() << "Packet captured. Length:" << pkthdr->len;
    analyzeTCPPacket(packet, pkthdr->len, wardenFort);
}

void captureTCPPackets(pcap_if_t* adapter, WardenFort& wardenFort) {
    char errbuf[PCAP_ERRBUF_SIZE];

    // Open the adapter for live capturing
    pcap_t* pcapHandle = pcap_open_live(adapter->name, BUFSIZ, 1, 1000, errbuf);
    if (pcapHandle == nullptr) {
        qDebug() << adapter;
        qDebug() << "Error opening adapter for capturing:" << errbuf;
        return;
    }

    // Apply a filter to capture only TCP packets
    struct bpf_program filter;
    if (pcap_compile(pcapHandle, &filter, "tcp", 0, PCAP_NETMASK_UNKNOWN) == -1) {
        qDebug() << "Error compiling filter:" << pcap_geterr(pcapHandle);
        pcap_close(pcapHandle);
        return;
    }
    if (pcap_setfilter(pcapHandle, &filter) == -1) {
        qDebug() << "Error setting filter:" << pcap_geterr(pcapHandle);
        pcap_freecode(&filter);
        pcap_close(pcapHandle);
        return;
    }
    pcap_freecode(&filter);

    // Start capturing packets
    pcap_loop(pcapHandle, 0, packetHandler, reinterpret_cast<u_char*>(&wardenFort));

    // Close the capture handle when done
    pcap_close(pcapHandle);
}


class CaptureThread : public QThread {
public:
    explicit CaptureThread(pcap_if_t* adapter, WardenFort& wardenFort) : adapter(adapter), wardenFort(wardenFort) {}

protected:
    void run() override {
        captureTCPPackets(adapter, wardenFort);
    }

private:
    pcap_if_t* adapter;
    WardenFort& wardenFort;
};

void scanActiveLANAdapters(WardenFort& wardenFort) {
    char errbuf[PCAP_ERRBUF_SIZE];

    // Get a list of all available network adapters
    pcap_if_t* allAdapters;
    if (pcap_findalldevs(&allAdapters, errbuf) == -1) {
        qDebug() << "Error finding adapters:" << errbuf;
        return;
    }

    // Iterate over the list of adapters
    for (pcap_if_t* adapter = allAdapters; adapter != nullptr; adapter = adapter->next) {
        if (adapter->name != nullptr && !isFilteredAdapter(adapter)) {
            // Display the name and description of the LAN adapter
            qDebug() << "Active LAN adapter found:" << adapter->name << "Description:" << (adapter->description ? adapter->description : "No Description");

            // Start capturing TCP packets from this adapter in a separate thread
            CaptureThread* thread = new CaptureThread(adapter, wardenFort);
            thread->start();
        }
    }

    // Free the list of adapters
    pcap_freealldevs(allAdapters);
}

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    WardenFort w;
    w.show();

    // Call the function to scan active LAN adapters and capture TCP packets
    scanActiveLANAdapters(w); // Pass the WardenFort object as an argument

    return a.exec();
}
