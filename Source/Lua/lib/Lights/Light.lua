Light = {}

function Light.new()
	local self = {}

	-- Public member variables
	self.shadows = false

	-- Public methods
	function self.castsShadows(flag)
		self.shadows = flag
		return self
	end

	return self
end

return Light