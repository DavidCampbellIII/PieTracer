#pragma once

#include <memory>
#include <vector>

class Traceable;
struct Light;

class World
{
public:
	World() = default;

	[[nodiscard]] const std::vector<std::shared_ptr<Traceable>>& GetTraceables() const { return traceables; }
	[[nodiscard]] const std::vector<std::shared_ptr<Light>>& GetLights() const { return lights; }

	void AddTraceable(const std::shared_ptr<Traceable>& object) { traceables.push_back(object); }
	void AddLight(const std::shared_ptr<Light>& light) { lights.push_back(light); }
	
private:
	std::vector<std::shared_ptr<Traceable>> traceables;
	std::vector<std::shared_ptr<Light>> lights;
};