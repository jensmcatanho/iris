local Object = require('Object')

local Sphere = {
	Radius = 1,
	Center = {x = 0.0, y = 0.0, z = 0.0}
}

function Sphere:new(r, g, b)
	local instance = Object:new(r, g, b)

	setmetatable(instance, self)
	setmetatable(self, {__index = Object})
	self.__index = self

	return instance
end

function Sphere:SetCenter(x, y, z)
	self.Center.x, self.Center.y, self.Center.z = x, y, z
end

function Sphere:SetRadius(r)
	self.Radius = r
end

return Sphere