module github.com/v6d-io/v6d/k8s

go 1.16

require (
	github.com/go-logr/logr v0.4.0
	github.com/onsi/ginkgo v1.16.4
	github.com/onsi/gomega v1.15.0
	k8s.io/api v0.20.2
	k8s.io/apimachinery v0.20.2
	k8s.io/client-go v0.20.2
	k8s.io/code-generator v0.19.11
	k8s.io/klog/v2 v2.2.0
	k8s.io/kube-scheduler v0.19.11 // indirect
	k8s.io/kubernetes v0.19.11
	sigs.k8s.io/controller-runtime v0.8.3
)

replace (
	github.com/googleapis/gnostic => github.com/googleapis/gnostic v0.4.2
	k8s.io/api => k8s.io/api v0.19.11
	k8s.io/apiextensions-apiserver => k8s.io/apiextensions-apiserver v0.19.11
	k8s.io/apimachinery => k8s.io/apimachinery v0.19.11
	k8s.io/apiserver => k8s.io/apiserver v0.19.11
	k8s.io/cli-runtime => k8s.io/cli-runtime v0.19.11
	k8s.io/client-go => k8s.io/client-go v0.19.11
	k8s.io/cloud-provider => k8s.io/cloud-provider v0.19.11
	k8s.io/cluster-bootstrap => k8s.io/cluster-bootstrap v0.19.11
	k8s.io/code-generator => k8s.io/code-generator v0.19.11
	k8s.io/component-base => k8s.io/component-base v0.19.11
	k8s.io/cri-api => k8s.io/cri-api v0.19.11
	k8s.io/csi-translation-lib => k8s.io/csi-translation-lib v0.19.11
	k8s.io/kube-aggregator => k8s.io/kube-aggregator v0.19.11
	k8s.io/kube-controller-manager => k8s.io/kube-controller-manager v0.19.11
	k8s.io/kube-proxy => k8s.io/kube-proxy v0.19.11
	k8s.io/kube-scheduler => k8s.io/kube-scheduler v0.19.11
	k8s.io/kubectl => k8s.io/kubectl v0.19.11
	k8s.io/kubelet => k8s.io/kubelet v0.19.11
	k8s.io/kubernetes => k8s.io/kubernetes v1.19.11
	k8s.io/legacy-cloud-providers => k8s.io/legacy-cloud-providers v0.19.11
	k8s.io/metrics => k8s.io/metrics v0.19.11
	k8s.io/sample-apiserver => k8s.io/sample-apiserver v0.19.11
)
