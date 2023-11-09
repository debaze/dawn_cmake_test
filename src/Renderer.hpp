#pragma once

class Renderer {
	private:
		wgpu::Instance instance;
		void (*adapterAndDeviceCallback)(Renderer& renderer);
		wgpu::Adapter adapter;
		wgpu::Device device;
		GLFWwindow* window;
		wgpu::Surface surface;
		wgpu::SwapChain swapChain;
		wgpu::ShaderModule vertexShaderModule;
		wgpu::ShaderModule fragmentShaderModule;
		wgpu::RenderPipeline renderPipeline;
		std::vector<wgpu::Buffer> buffers;
	public:
		wgpu::Buffer vertexBuffer;

	public:
		~Renderer();

		const wgpu::SwapChain& getSwapChain() const;
		const wgpu::Device& getDevice() const;
		const wgpu::RenderPipeline& getRenderPipeline() const;
		void setAdapterAndDeviceCallback(void (*callback)(Renderer& renderer));
		void setWindow(GLFWwindow* window);
		const wgpu::Buffer& getBuffer(uint32_t id) const;

		void createInstance();
		void requestAdapterAndDevice();
		void createSurface();
		void createSwapChain();
		wgpu::ShaderModule createShaderModule(const char* source);
		void createRenderPipeline(wgpu::ShaderModule& vertexShaderModule, wgpu::ShaderModule& fragmentShaderModule, const wgpu::VertexBufferLayout& vertexBufferLayout);
		wgpu::Buffer createBuffer(const wgpu::BufferDescriptor& descriptor);
};