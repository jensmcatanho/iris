local Object = {
	Color = {r = 0, g = 0, b = 0},

}

function Object:new(r, g, b)
	local instance = {}

	setmetatable(instance, self)
	self.__index = self

	self.Color.r, self.Color.g, self.Color.b = r, g, b

	return instance
end

function Object:SetColor(r, g, b)
	self.Color.r, self.Color.g, self.Color.b = r, g, b
end

return Object