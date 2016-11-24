local Sampler = require('Image.Sampler')

Image = {}

function Image.new(w, h)
	local self = {}

	-- Public member variables
	self.width = w
	self.height = h
	self.pixel_size = 1.0
	self.should_sample = true
	self.sampler = Sampler.MultiJittered
	self.samples = 16
	self.sets = 83

	return self
end

return Image
