Object = {}

function Object.new()
	local self = {}

	-- Public member variables
	self.material = false

	-- Public methods
	function self.AddMaterial(material)
		self.material = material
	end

	return self
end

return Object
