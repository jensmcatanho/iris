local Object = require('Object')

local Plane = {
	Point = {x = 0.0, y = 0.0, z = 0.0},
	Normal = {x = 0.0, y = 1.0, z = 0.0}
}

function Plane:new(r, g, b)
	local instance = Object:new(r, g, b)

	setmetatable(instance, self)
	setmetatable(self, {__index = Object})
	self.__index = self

	return instance
end

function Plane:SetPoint(x, y, z)
	self.Point.x, self.Point.y, self.Point.z = x, y, z
end

function Plane:SetNormal(x, y, z)
	self.Normal.x, self.Normal.y, self.Normal.z = x, y, z
end

return Plane