import HomeHeader from '@/components/HomeHeader';
import HomeSearch from '@/components/HomeSearch';
import Image from 'next/image';

export default function Home() {
    return (
        <>
            <HomeHeader />
            <div className='flex flex-col items-center mt-18'>
                <Image
                    src='/logo.png'
                    alt='Nostr Book Users'
                    width={150}
                    height={100}
                    priority
                    style={{ width: 'auto' }}
                />
                <h2 
                    style={{ fontSize: 24 }}
                    className="text-gray-400 font-bold"
                >
                    Nostr Book - Search Users
                </h2>
                <HomeSearch />
            </div>
        </>
    );
}
