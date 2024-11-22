#include "Protos.h"
#include "utils.h"

#include <arpa/inet.h>

Protos::Protos(uint32_t ssrc): ssrc(ssrc) {}

void Protos::CreateRTPHeader(RTPHeader *header, unsigned short seqNum, unsigned int timestamp) {
    header->version = 2;
    header->p = 0;
    header->x = 0;
    header->cc = 0;
    header->m = 0;
    header->pt = 111;  // 0 for PCMU (G.711 µ-law) , 111 (Opus)
    header->seqNum = htons(seqNum);
    header->timestamp = htonl(timestamp);
    header->ssrc = htonl(ssrc);
}

void Protos::CreateSR(SenderReport *sr, unsigned int timestamp, unsigned int packetCount, unsigned int octetCount) {
    sr->version = 2;
    sr->p = 0;
    sr->rc = 0;
    sr->pt = 200;
    sr->length = htons(6);
    sr->ssrc = htonl(ssrc);

    auto time = utils::GetTime();
    sr->ntpTimestampMsw = htonl((uint32_t)(time >> 32));
    sr->ntpTimestampLsw = htonl((uint32_t)(time & 0xFFFFFFFF));
    sr->rtpTimestamp = htonl(timestamp);
    sr->senderPacketCount = htonl(packetCount);
    sr->senderOctetCount = htonl(octetCount);
}