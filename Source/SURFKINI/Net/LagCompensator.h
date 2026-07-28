#pragma once
// Following line added by Claude

class LagCompensator
{
public:
	LagCompensator();
	~LagCompensator();

	// Ring buffer to store historical player hitbox transforms up to 1000ms
	std::vector<std::pair<int, float>> historicalTransforms;
	void addTransform(int clientId, float timestamp);
	void validateClientFireTimestamps(int clientId, float fireTimestamp);
	void rewindHitbox(int clientId, float timestamp);
	void compensateLag(float lagAmount);
	// UDP socket for native server-client communication
	ENet::UdpSocket* socket;
};