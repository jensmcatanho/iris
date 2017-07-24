local Sampler = require('Image.Sampler')

Image = {}

function Image.new()
	local self = {}

	-- Public member variables
	self.width = 400
	self.height = 400
	self.pixel_size = 1.0
	self.gamma_correction = 1.0
	self.background_color = {r = 0.0, g = 0.0, b = 0.0}
	self.clamp_out_of_gamut = false
	self.clamp_color = {r = 1.0, g = 1.0, b = 1.0}
	self.should_sample = true
	self.sampler = Sampler.MultiJittered
	self.samples = 16
	self.sets = 83

	-- Public methods
	function self.across(w, h)
		self.width, self.height = w, h
		return self
	end

	function self.withPixelSize(p)
		self.pixel_size = p
		return self
	end

	function self.withGammaCorrection(gamma)
		self.gamma_correction = gamma
		return self
	end

	function self.withBackgroundColor(r, g, b)
		self.background_color.r, self.background_color.g, self.background_color.b = r, g, b
		return self
	end

	function self.shouldClamp(flag)
		self.clamp_out_of_gamut = flag
		return self
	end

	function self.withClampColor(r, g, b)
		self.clamp_color.r, self.clamp_color.g, self.clamp_color.b = r, g, b
		return self
	end

	function self.shouldSample(flag)
		self.should_sample = flag
		return self
	end

	function self.withSampler(s)
		self.sampler = s
		return self
	end

	function self.withSamples(s)
		self.samples = s
		return self
	end

	function self.withSets(s)
		self.sets = s
		return self
	end

	return self
end

return Image
