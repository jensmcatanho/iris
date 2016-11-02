local Object = require('Object')
local Sphere = require('Sphere')
local Plane = require('Plane')
local Image = require('Image')

local SceneManager = {
	Objects = { },
	numObjects = 0
}

function SceneManager:new()
	local instance = {}

	setmetatable(instance, self)
	self.__index = self

	return instance
end

function SceneManager:addObject(new_obj)
	table.insert(self.Objects, new_obj)
end

return SceneManager