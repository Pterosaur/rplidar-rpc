// Generated by the gRPC protobuf plugin.
// If you make any local change, they will be lost.
// source: lidar.proto

#include "lidar.pb.h"
#include "lidar.grpc.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/channel_interface.h>
#include <grpc++/impl/codegen/client_unary_call.h>
#include <grpc++/impl/codegen/method_handler_impl.h>
#include <grpc++/impl/codegen/rpc_service_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/sync_stream.h>
namespace device {

static const char* lidar_server_method_names[] = {
  "/device.lidar_server/create",
  "/device.lidar_server/start",
  "/device.lidar_server/stop",
  "/device.lidar_server/get_points",
};

std::unique_ptr< lidar_server::Stub> lidar_server::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  std::unique_ptr< lidar_server::Stub> stub(new lidar_server::Stub(channel));
  return stub;
}

lidar_server::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_create_(lidar_server_method_names[0], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_start_(lidar_server_method_names[1], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_stop_(lidar_server_method_names[2], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_get_points_(lidar_server_method_names[3], ::grpc::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status lidar_server::Stub::create(::grpc::ClientContext* context, const ::device::connect_info& request, ::device::token* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_create_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::device::token>* lidar_server::Stub::AsynccreateRaw(::grpc::ClientContext* context, const ::device::connect_info& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::device::token>(channel_.get(), cq, rpcmethod_create_, context, request);
}

::grpc::Status lidar_server::Stub::start(::grpc::ClientContext* context, const ::device::token& request, ::google::protobuf::Empty* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_start_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* lidar_server::Stub::AsyncstartRaw(::grpc::ClientContext* context, const ::device::token& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>(channel_.get(), cq, rpcmethod_start_, context, request);
}

::grpc::Status lidar_server::Stub::stop(::grpc::ClientContext* context, const ::device::token& request, ::google::protobuf::Empty* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_stop_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* lidar_server::Stub::AsyncstopRaw(::grpc::ClientContext* context, const ::device::token& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>(channel_.get(), cq, rpcmethod_stop_, context, request);
}

::grpc::Status lidar_server::Stub::get_points(::grpc::ClientContext* context, const ::device::token& request, ::device::lidar_raw_points* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_get_points_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::device::lidar_raw_points>* lidar_server::Stub::Asyncget_pointsRaw(::grpc::ClientContext* context, const ::device::token& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::device::lidar_raw_points>(channel_.get(), cq, rpcmethod_get_points_, context, request);
}

lidar_server::Service::Service() {
  (void)lidar_server_method_names;
  AddMethod(new ::grpc::RpcServiceMethod(
      lidar_server_method_names[0],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< lidar_server::Service, ::device::connect_info, ::device::token>(
          std::mem_fn(&lidar_server::Service::create), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      lidar_server_method_names[1],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< lidar_server::Service, ::device::token, ::google::protobuf::Empty>(
          std::mem_fn(&lidar_server::Service::start), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      lidar_server_method_names[2],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< lidar_server::Service, ::device::token, ::google::protobuf::Empty>(
          std::mem_fn(&lidar_server::Service::stop), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      lidar_server_method_names[3],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< lidar_server::Service, ::device::token, ::device::lidar_raw_points>(
          std::mem_fn(&lidar_server::Service::get_points), this)));
}

lidar_server::Service::~Service() {
}

::grpc::Status lidar_server::Service::create(::grpc::ServerContext* context, const ::device::connect_info* request, ::device::token* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status lidar_server::Service::start(::grpc::ServerContext* context, const ::device::token* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status lidar_server::Service::stop(::grpc::ServerContext* context, const ::device::token* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status lidar_server::Service::get_points(::grpc::ServerContext* context, const ::device::token* request, ::device::lidar_raw_points* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace device
