Object = {}

function Object.new()
	local self = {}

	-- Public member variables
	self.material = false

	-- Public methods
	function self.withMaterial(m)
		self.material = m
		return self
	end

	return self
end

return Object
