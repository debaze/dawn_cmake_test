#include "Renderer.hpp"

const wgpu::SwapChain& Renderer::getSwapChain() const {
	return swapChain;
}

const wgpu::Device& Renderer::getDevice() const {
	return device;
}

const wgpu::RenderPipeline& Renderer::getRenderPipeline() const {
	return renderPipeline;
}

/* const wgpu::Buffer& Renderer::getBuffer(uint32_t id) const {
	return buffers.at(id);
} */

void Renderer::setAdapterAndDeviceCallback(void (*callback)(Renderer& renderer)) {
	adapterAndDeviceCallback = callback;
}

void Renderer::setWindow(GLFWwindow* window) {
	this->window = window;
}

void Renderer::createInstance() {
	instance = wgpu::CreateInstance(nullptr);
}

void Renderer::requestAdapterAndDevice() {
	instance.RequestAdapter(
		nullptr,
		[](WGPURequestAdapterStatus status, WGPUAdapter adapter, const char*, void* userData) {
			if (status != WGPURequestAdapterStatus_Success) {
				exit(EXIT_FAILURE);
			}

			Renderer& renderer = *reinterpret_cast<Renderer*>(userData);
			renderer.adapter = wgpu::Adapter::Acquire(adapter);
			renderer.adapter.RequestDevice(
				nullptr,
				[](WGPURequestDeviceStatus status, WGPUDevice device, const char*, void* userData) {
					if (status != WGPURequestDeviceStatus_Success) {
						exit(EXIT_FAILURE);
					}

					Renderer& renderer = *reinterpret_cast<Renderer*>(userData);

					renderer.device = wgpu::Device::Acquire(device);
					renderer.adapterAndDeviceCallback(renderer);
				},
				userData
			);
		},
		(void*) this
	);
}

void Renderer::createSurface() {
	#ifdef EMSCRIPTEN
		wgpu::SurfaceDescriptorFromCanvasHTMLSelector canvasDescriptor {};
		canvasDescriptor.selector = "#output";

		wgpu::SurfaceDescriptor surfaceDescriptor {
			.nextInChain = &canvasDescriptor,
		};

		surface = instance.CreateSurface(&surfaceDescriptor);
	#else
		surface = wgpu::glfw::CreateSurfaceForWindow(instance, window);
	#endif
}

void Renderer::createSwapChain() {
	int width;
	int height;

	glfwGetWindowSize(window, &width, &height);

	wgpu::SwapChainDescriptor swapChainDescriptor {
		.usage = wgpu::TextureUsage::RenderAttachment,
		.format = wgpu::TextureFormat::BGRA8Unorm,
		.width = (uint32_t) width,
		.height = (uint32_t) height,
		.presentMode = wgpu::PresentMode::Fifo,
	};

	swapChain = device.CreateSwapChain(surface, &swapChainDescriptor);
}

wgpu::ShaderModule Renderer::createShaderModule(const char* source) {
	wgpu::ShaderModuleWGSLDescriptor shaderModuleWGSLDescriptor {};
	shaderModuleWGSLDescriptor.code = source;

	wgpu::ShaderModuleDescriptor shaderModuleDescriptor {
		.nextInChain = (wgpu::ChainedStruct*) &shaderModuleWGSLDescriptor,
	};

	return device.CreateShaderModule(&shaderModuleDescriptor);
}

void Renderer::createRenderPipeline(wgpu::ShaderModule& vertexShaderModule, wgpu::ShaderModule& fragmentShaderModule /*, const wgpu::VertexBufferLayout& vertexBufferLayout */) {
	this->vertexShaderModule = vertexShaderModule;
	this->fragmentShaderModule = fragmentShaderModule;

	wgpu::ColorTargetState colorTargetState {
		.format = wgpu::TextureFormat::BGRA8Unorm,
	};

	wgpu::FragmentState fragmentState {
		.module = fragmentShaderModule,
		.entryPoint = "main",
		.targetCount = 1,
		.targets = &colorTargetState,
	};

	wgpu::RenderPipelineDescriptor renderPipelineDescriptor {
		.vertex = {
			.module = vertexShaderModule,
			.entryPoint = "main",
			// .bufferCount = 1,
			// .buffers = &vertexBufferLayout,
		},
		.fragment = &fragmentState,
	};

	renderPipeline = device.CreateRenderPipeline(&renderPipelineDescriptor);
}

/* wgpu::Buffer Renderer::createBuffer(const wgpu::BufferDescriptor& bufferDescriptor) {
	wgpu::Buffer buffer = device.CreateBuffer(&bufferDescriptor);

	buffers.push_back(buffer);

	return buffer;
} */

Renderer::~Renderer() {
	device.Destroy();
}