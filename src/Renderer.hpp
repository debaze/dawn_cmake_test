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

	public:
		const wgpu::SwapChain& getSwapChain() const;
		const wgpu::Device& getDevice() const;
		const wgpu::RenderPipeline& getRenderPipeline() const;
		void setAdapterAndDeviceCallback(void (*callback)(Renderer& renderer));
		void setWindow(GLFWwindow* window);

		void createInstance();
		void requestAdapterAndDevice();
		void createSurface();
		void createSwapChain();
		wgpu::ShaderModule createShaderModule(const char* source);
		void createRenderPipeline(wgpu::ShaderModule& vertexShaderModule, wgpu::ShaderModule& fragmentShaderModule);

		~Renderer();
};