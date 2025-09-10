/** @type {import('next').NextConfig} */
const nextConfig = {
    experimental: {
        missingSuspenseWithCSRBailout: false 
    },
    images: {
        remotePatterns: [],
        //unoptimized: true
    },
};

module.exports = nextConfig;
